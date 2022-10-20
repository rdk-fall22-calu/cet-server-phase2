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
    // blue:                    \033[0;34m
    // red:                     \033[0;31m
    // reset to default color:  \033[0m
    //Quit formatting
    
    return "\033[0;34m╔══════════════════╗\n"
            "║       Quit       ║\n"
            "╚══════════════════╝\033[0m\n"

            "Quit disconnects the client and the server. It will return a response prior as such:\n"
           "\033[0;31m1#Disconnecting.\n\n"

    //Register formatting
            "\033[0;34m╔══════════════════╗\n"
            "║     Register     ║\n"
            "╚══════════════════╝\033[0m\n"

            "Registers a user with the server, as long as the user is part of the accepted list. Returns an informative"
           "response as a string as follows:\n"
           "If successful registration:\n"
           "\033[0;31m1#<User> successfully registered.\033[0m\n"
           "If previously registered:\n"
           "\033[0;31m0#<User> has registered previously.\033[0m\n\n"

    //MyInfo formatting
            "\033[0;34m╔═════════════════╗\n"
            "║     My Info     ║\n"
            "╚═════════════════╝\033[0m\n"

            "Requires the user to be registered. MyInfo returns the information about the user client listed below.\n"
           "\033[0;31mFull Name\033[0m in the format of 'FirstName LastName'\n"
           "\033[0;31mAge\033[0m, an integer between 18 and 22\n"
           "\033[0;31mGPA\033[0m, a float number between 2.5 and 4.0\n"
           "\033[0;31mIP Address\033[0m, the IP Address where the client is connected from\n"
           "This information is formatted as a string, with each piece of data delimited by ‘#’.\n"
           "Example:\n"
           "\033[0;31m1#Robert Krency#20#3.2#123.456.7.8\033[0m\n"
           "If User is not registered, this command returns the following string:\n"
           "\033[0;31m0#Command requires registered user.\033[0m\n\n"

    //Online users formatting
            "\033[0;34m╔══════════════════╗\n"
            "║   Online Users   ║\n"
            "╚══════════════════╝\033[0m\n"

            "Requires the user to be registered. OnlineUsers returns a list of currently active users, delimited by ‘#’.\n"
           "Example:\n"
           "\033[0;31m1#kre1188#chen#ste4864\033[0m\n"
           "If User is not registered, this command returns the following string:\n"
           "\033[0;31m0#Command requires registered user.\033[0m\n\n"

    //Registered users formatting
            "\033[0;34m╔══════════════════╗\n"
            "║ Registered Users ║\n"
            "╚══════════════════╝\033[0m\n"

            "Requires the user to be registered. RegisteredUsers returns a list of currently registered users, delimited by ‘#’.\n"
           "Example:\n"
           "\033[0;31m1#kre1188#chen#ste4864\033[0m\n"
           "If User is not registered, this command returns the following string:\n"
           "\033[0;31m0#Command requires registered user.\033[0m\n\n";
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