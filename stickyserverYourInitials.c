#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// StickyServer##.c task 2
//Worked with Tucker Lehtonen, Lucas Saunders, Hugh Seeley, Tyler Smith
#define PORT 8080       // Port number on which the server will listen
#define BACKLOG 5       // Maximum number of pending connections
#define BUFSIZE 1024    // Buffer size for data
#define MAX_NAME_LENGTH 30    //Self-Explanatory

int SocketSetupAndListen();
void closeConnection(int client_fd, int server_fd);
/*
2. If the user wants to sign up, the server must collect a username, a password, and a
full name. This information about username, password (unencrypted for this
exercise), and full name must be stored in an external text file on the server and read
into a linked list when the server starts up. The server must not allow any user to
sign up more than once. If someone tries to sign up again, it must present them with
a login screen. Authentication is based on username and password. The password
must be at least 8 characters in length. The username is at most 30 characters long
and must not contain spaces or start with a number. The full name should be no
more than 50 characters in length
 */

int main() {
SocketSetupAndListen();
while (1) {

}
    closeConnection();
    return 0;
}

//SocketSetupAndListen code taken directly from tcpserver.c by David Bethelmy
int  SocketSetupAndListen() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len; //a data type used to store the size of a socket address structure
    // When calling functions like accept(), you need to tell the system how big the sockaddr structure is.
    char buffer[BUFSIZE];
    int num_bytes;
    //Create a socket
    // AF_INET for IPv4, SOCK_STREAM for TCP.
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    // This line initializes the server_addr structure (which holds address info) by setting all its bytes to 0.
    // without this line, the server_addr structure might contain random garbage values in fields you’re not explicitly setting, and bind() might fall.
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on any interface
    server_addr.sin_port = htons(PORT); // Convert port number to network byte order

    //Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //Listen for incoming connections
    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    //Accept an incoming connection
    addr_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &addr_len);
    if (client_fd < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted from %s:%d\n",
           inet_ntoa(client_addr.sin_addr),
           // Converts the client’s IP address from binary to human-readable format (e.g. "192.168.1.10").
           ntohs(client_addr.sin_port));
    //Converts the port number from network byte order to host byte order.
    //Network order is big-endian (used across the internet).
    //Your machine might be little-endian → this ensures the port is readable.

    inet_ntoa(client_addr.sin_addr),
            // Converts the client’s IP address from binary to human-readable format (e.g. "192.168.1.10").
            ntohs(client_addr.sin_port);
    //Converts the port number from network byte order to host byte order.
    //Network order is big-endian (used across the internet).
    //Your machine might be little-endian → this ensures the port is readable.
    // 6. Receive data from the client
    num_bytes = recv(client_fd, buffer, BUFSIZE - 1, 0);
    if (num_bytes < 0) {
        perror("recv failed");
    } else {
        buffer[num_bytes] = '\0';  // Null-terminate the received data

        char newBuffer[BUFSIZE];
        // 7. Echo the message back to the client
    }
}

//closeConnection code taken directly from tcpserver.c by David Bethelmy
void closeConnection(int client_fd, int server_fd) {
    close(client_fd); // Connected socket (used to talk to a specific client)
    printf("Server terminated.\n");
    close(server_fd);// Listening socket (server waits here for clients)
}
