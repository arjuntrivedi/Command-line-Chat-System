#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    // Declare a socket descriptor
    int connection = 0;
    
    // Check if the program was run without any command line arguments.
    // If yes, then it runs in server mode.
    if(argc == 1) {
        // Server mode

        // Step 1: Pick a random port number
        srandom(getpid());
        int port = 0xc000 | (random()&0x3fff);

        // Prepare server address structure
        struct sockaddr_in ipOfServer;
        memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
        ipOfServer.sin_family = AF_INET;  // Internet protocol v4 addresses
        ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);  // Accept connection on any IP of the machine
        ipOfServer.sin_port = htons(port);  // Convert port number to network byte order

        // Create socket
        int listener = socket(AF_INET, SOCK_STREAM, 0);

        // Associate the socket with its address
        bind(listener, (struct sockaddr*)&ipOfServer, sizeof(ipOfServer));

        // Set the socket to listen for incoming connections
        listen(listener, 20);

        // Display this computer's IP addresses
        system("host $HOSTNAME:");
        printf("The server is now listening on port %d\n", port);

        // Accept incoming connection
        connection = accept(listener, (struct sockaddr*)NULL, NULL);

        // Close the listening socket
        close(listener);
    }
    // If the program is run with two command line arguments, then it runs in client mode.
    else if(argc == 3) {
        // Client mode

        // Parse the command line arguments
        char *ipstring = argv[1];  // The IP address of the server
        int port = atoi(argv[2]);  // The port number of the server

        // Prepare server address structure
        struct sockaddr_in ipOfServer;
        memset(&ipOfServer, 0, sizeof(struct sockaddr_in));

        ipOfServer.sin_family = AF_INET;
        ipOfServer.sin_addr.s_addr = inet_addr(ipstring);
        ipOfServer.sin_port = htons(port);

        // Create socket
        connection = socket(AF_INET, SOCK_STREAM, 0);

        // Establish a connection to the server
        connect(connection, (struct sockaddr*)&ipOfServer, sizeof(ipOfServer));
    }
    else {
        // If an invalid number of command line arguments are provided, inform the user and exit.
        printf("Incorrect number of arguments\n");
        return 0;
    }

    // Set up polling
    struct pollfd fds[2];
    int timeout = 60000;  // Timeout for poll

    // Setting up file descriptors for polling
    fds[0].fd = STDIN_FILENO;  // File descriptor for standard input
    fds[1].fd = connection;    // File descriptor for the socket
    fds[0].events = POLLIN;    // Check for incoming data (read)
    fds[1].events = POLLIN;    // Check for incoming data (read)

    // Main loop: keep checking for and handling data on the sockets
    for(;;) {
        // Wait for an event on the sockets
        int pollReturn = poll(fds, 2, timeout);
        if(pollReturn > 0) {  // If there is an event
            // Check if there's incoming data on stdin
            if(fds[0].revents & POLLIN) {
                char buffer[4096];
                // Read data from stdin
                int bytesOutput = read(STDIN_FILENO, buffer, sizeof(buffer)-1);
                // Write data to the socket
                write(connection, buffer, bytesOutput);
            }
            // Check if there's incoming data on the socket
            if(fds[1].revents & POLLIN) {
                char buffer[4096];
                // Read data from the socket
                int bytesOutput = read(connection, buffer, sizeof(buffer)-1);
                // Write data to stdout
                write(STDOUT_FILENO, buffer, bytesOutput);
            }
        }
    }
    // Close the connection
    close(connection);
    return 0;
} 