/**
 * @file commands.h
 * @author Distint Howie (how4685@pennwest.edu)
 * @author Robert Krency (kre1188@pennwest.edu)
 * @author Anthony Stepich (ste4864@pennwest.edu)
 * @brief 
 * 
 */


#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#define CMD_HELP "HELP"
#define CMD_QUIT "QUIT"
#define CMD_REGISTER "REGISTER"
#define CMD_MYINFO "MYINFO"
#define CMD_ONLINE_USERS "ONLINEUSERS"
#define CMD_REGISTERED_USERS "REGISTEREDUSERS"

/**
 * @brief 
 * 
 * @return char* 
 */
char* execute_help();   // If the user inputs this command the server will respond with a string of all accepted commands

/**
 * @brief 
 * 
 * @return char* 
 */
char* execute_quit();   // If the user inputs this command the server will  disconnect them and respond with a string telling them that they have been disconnected 

/**
 * @brief 
 * 
 * @param userID 
 * @return char* 
 */
char* execute_register(char* userID);   /* If the user inputs this command the server will attempt to register them and respond with
                                         a string telling them that their userID has been registered successfully or not
                                         possible reasons are it was already registered or it is an invalid userID*/
                                        

/**
 * @brief 
 * 
 * @param userID 
 * @return char* 
 */
char* execute_myinfo(char* userID);   /* If the user inputs this command the server will respond with a string of their name,age,GPA,and IP address
                                      name is in the format Firstname Lastname, age is an integer between 18 and 22, GPA is a float between 2.5 and 4.0,
                                      and Their IP address*/
/**
 * @brief 
 * 
 * @param userID 
 * @return char* 
 */
char* execute_online_users(char* userID);   // If the user iputs this command the server will respond with a string of all online users

/**
 * @brief 
 * 
 * @param userID 
 * @return char* 
 */
char* execute_registered_users(char* userID);   // If the user inputs this command the server will respond with a string of all registered users


#endif
