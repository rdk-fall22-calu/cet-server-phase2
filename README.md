# cet-server-phase2
Phase 2 of the Server program for ACET 440 at PennWest.

## Supported Client Commands:

For any commands that require a registered user, failure 

- Help: a list of all acceptable commands
- Register: registers a user if they are not previously registered 
- MyInfo: when a registered client sends this command, the server will send the following info:
  - Full name in the format of "FirstName LastName"
  - Age, a random integer between 18 and 22
  - GPA, a random float number between 2.5 and 4
  - IP Address, the IP Address where the client is from
- Quit: Disconnects the client
- RegisteredUsers: Returns a list of all currently registered users
- OnlineUsers: Returns a list of all currently online users
- 