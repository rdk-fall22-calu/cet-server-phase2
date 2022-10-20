

#include <stdlib.h>

#include "logging.h"
#include "users.h"


int main()
{
    log_message("SERVER", "Starting server.");

    // Load the accepted users list from file
    if(!load_users_list())
    {
        log_message("SERVER", "Unable to load accepted users list, exiting.");
        exit(0);
    }

    


}

