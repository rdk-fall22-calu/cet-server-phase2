

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "logging.h"
#include "users.h"


#define RCV_BUFFER_SIZE 1024
#define SND_BUFFER_SIZE 1024
#define PORT 4400

int clientNumber = 0; // Store how many clients are connected

// Threading Function
void *connection_handler(void *);

int main()
{
    log_message("SERVER", "Starting server.");

    // Load the accepted users list from file
    if(!load_users_list())
    {
        log_message("SERVER", "Unable to load accepted users list, exiting.");
        return 1;
    }

    // Initialize the server
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    // Create the Socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) // Socket failed, exit
    {
        log_message("SERVER", "Socket creation failed, exiting.");
        return 1;
    }
    else
    {
        log_message("SERVER", "Socket created.");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 4400 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        log_message("SERVER", "Bind failed.");
        return 1;
    }
    log_message("SERVER", "Bind successful.");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept any incoming connection
    log_message("SERVER", "Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        log_message("SERVER", "Connection accepted.");
        	clientNumber ++; //increase the number of connected clients
         
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            log_message("SERVER", "Could not create thread. Exiting...");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        log_message("SERVER", "Handler assigned.");
    }
     
    if (client_sock < 0)
    {
        log_message("SERVER", "Accept failed. Exiting...");
        return 1;
    }
     
    log_message("SERVER", "Exiting...");
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , mymessage[2000],  client_message[2000], threadName[20];
    snprintf(threadName, sizeof(threadName), "SERVER\\%d", clientNumber);
     
    //Send some messages to the client
    snprintf(mymessage, sizeof(mymessage), "Greetings! You are the No.%d client. I am your connection handler\n", clientNumber);
    message = mymessage;
    write(sock , message , strlen(message));
     
    message = "Now type something and i shall repeat what you type \n";
    write(sock , message , strlen(message));
     
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //end of string marker
		client_message[read_size] = '\0';
		
		//Send the message back to client
        write(sock , client_message , strlen(client_message));
		
		//clear the message buffer
		memset(client_message, 0, 2000);
    }
     
    if(read_size == 0)
    {
        log_message(threadName, "Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        log_message(threadName, "Receive failed");
    }
         
    return 0;
} 

