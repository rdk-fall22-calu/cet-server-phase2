/**
 * @file commands.c
 * @author 
 * @brief 
 * 
 */


#include "users.h"
#include <stdlib.h>

char* execute_help()
{
    return 0;
}

char* execute_quit()
{
    return "1#Disconnecting.";
}

char* execute_register(char* userID)
{
    // Get the user
    struct user *user = get_user(userID);

    // Check if the user exists
    if (user == NULL)
        return "0#Unable to register user.";

    // Check if the user is registered
    if (user->status == REGISTERED)
        return "0#User is already registered.";

    // Change user's status to registered.
    

}

char* execute_myinfo(char* userID);

char* execute_online_users(char* userID);

char* execute_registered_users(char* userID);
