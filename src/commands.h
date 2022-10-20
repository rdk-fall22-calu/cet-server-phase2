/**
 * @file commands.h
 * @author your name (you@domain.com)
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
char* execute_help();

/**
 * @brief 
 * 
 * @return char* 
 */
char* execute_quit();

/**
 * @brief 
 * 
 * @param userID 
 * @return char* 
 */
char* execute_register(char* userID);

/**
 * @brief 
 * 
 * @param userID 
 * @return char* 
 */
char* execute_myinfo(char* userID);

/**
 * @brief 
 * 
 * @param userID 
 * @return char* 
 */
char* execute_online_users(char* userID);

/**
 * @brief 
 * 
 * @param userID 
 * @return char* 
 */
char* execute_registered_users(char* userID);


#endif