/**
 * @file users.h
 * @author Distint Howie (how4685@pennwest.edu)
 * @author Robert Krency (kre1188@pennwest.edu)
 * @author Anthony Stepich (ste4864@pennwest.edu)
 * @brief Defines the registered users 
 * 
 */

#ifndef __USERS_H__
#define __USERS_H__

#define NUM_USERS 27
#define REGISTERED 1
#define UNREGISTERED 0

#define FILE_READ "r"
#define FILE_WRITE "w"
#define FILE_BUFFER_SIZE 256
#define ACCEPTED_USERS_FILE "names.txt"
#define USER_DATA_FILE "users.csv"
#define CSV_DELIMITER ","

#define DEFAULT_IP_ADDRESS "-1.-1.-1.-1"


/**
 * @brief Defines a User
 * 
 */
struct user {
    char userID[10];
    char name[50];
    int age;
    float gpa;
    char address[50]; // IP Address user is connected from
    int status;
};

static struct user userList[NUM_USERS];

/**
 * @brief Loads the list of accepted users from the file names.txt
 * 
 * @return int 1 for successful loading, 0 for failed to load
 */
int load_users_list();


/**
 * @brief 
 * will give all users Their appropriate ID and first and last name and will assign them an age between 18 and 20, a GPA between 2.5 and 4.0 
 */
int initialize_users();


/**
 * @brief 
 * 
 */
void save_user_data();


/**
 * @brief Returns the user with the specified user ID
 * Pre-condition: The user exists
 * Returns null if the user does not exist
 */
struct user* get_user(char *userID);


/**
 * @brief 
 * 
 */
struct user* get_user_list();

#endif
