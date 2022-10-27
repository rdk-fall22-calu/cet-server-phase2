

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
#include "commands.h"

#define RCV_BUFFER_SIZE 1024
#define SND_BUFFER_SIZE 1024
#define PORT 4400

int clientNumber = 0; // Store how many clients are connected

// Threading Function
void *connection_handler(void *);

// Convert a string to full upper case
char *strupr(char * text);

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
    log_message("SERVER", "Socket created.");

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
    char *message , mymessage[2000],  client_message[2000], threadName[20],
         *userID, displayMessage[2000];
    snprintf(threadName, sizeof(threadName), "SERVER\\%d", clientNumber);
     
    // Greet the Client
    snprintf(displayMessage, sizeiof(displayMessage), "Connecting to client on thread %d", clientNumber);
    log_message(threadName, displayMessage);

    snprintf(mymessage, sizeof(mymessage), "Greetings! You are the No.%d client. I am your connection handler.\n", clientNumber);
    message = mymessage;
    write(sock , message , strlen(message));

    // Get the User ID
    message = "Please input your User ID.\n";
    write(sock , message , strlen(message));

    // TODO: Get the user ID after first connection
    
     
    //Receive a message from client
    int quit = 0;
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //end of string marker
		client_message[read_size] = '\0';
        client_message = strupr(client_message);

        // Determie the command
        if (strcmp(client_message, CMD_HELP))
        {
            log_message(threadName, "Executing HELP command.");
            client_message = execute_help();
        }
        else if (strcmp(client_message, CMD_QUIT))
        {
            log_message(threadName, "Executing QUIT command.");
            client_message = execute_quit();
            quit = 1;
        }
        else if (strcmp(client_message, CMD_REGISTER))
        {
            log_message(threadName, "Executing REGISTER command.");
            client_message = execute_register(userID);
        }
        else if (strcmp(client_message, CMD_MYINFO))
        {
            log_message(threadName, "Executing MYINFO command.");
            client_message = execute_myinfo(userID);
        }
        else if (strcmp(client_message, CMD_ONLINE_USERS))
        {
            log_message(threadName, "Executing ONLINEUSERS command.");
            client_message = execute_online_users(userID);
        }
        else if (strcmp(client_message, CMD_REGISTERED_USERS))
        {
            log_message(threadName, "Executing REGISTEREDUSERS command.");
            client_message = execute_registered_users(userID);
        }
        else 
        {
            snprintf(displayMessage, sizeof(displayMessage), "Command not recognized. Client message: \n\n\t %s \n\n", client_message);
            log_message(threadName, displayMessage);
            client_message = "0#Command not recognized.";
        }
		
		//Send the message back to client
        write(sock , client_message , strlen(client_message));
		
		//clear the message buffer
		memset(client_message, 0, 2000);

        // Disconnect
        if (quit == 1)
            break;
    }
     
    if(read_size == 0)
    {
        log_message(threadName, "Client disconnected.");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        log_message(threadName, "Receive failed.");
    }
         
    return 0;
} 

char *strupr(char * text)
{
	int i, j=strlen(text);
	
	for (i=0;i<j;i++)
	{
		if ((text[i]>=97)&&(text[i]<=122))
			text[i]=text[i]-32;
	}
	return text;
}
