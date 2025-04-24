
// StickyServer##.c task 2
//Worked with Tucker Lehtonen, Lucas Saunders, Hugh Seeley, Tyler Smith, Daniel Sanchez, conner
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080 // Port number on which the server will listen
#define BACKLOG 5 // Maximum number of pending connections
#define BUFSIZE 1024 // Buffer size for data
int main() {
int server_fd, client_fd;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_len; //a data type used to store the size of a socket address
structure
// When calling functions like accept(), you need to tell the system how big
the sockaddr structure is.
char buffer[BUFSIZE];
int num_bytes;
// 1. Create a socket
// AF_INET for IPv4, SOCK_STREAM for TCP.
server_fd = socket(AF_INET, SOCK_STREAM, 0);
if (server_fd < 0) {
perror("socket failed");
exit(EXIT_FAILURE);
}
// 2. Set up the server address structure
memset(&server_addr, 0, sizeof(server_addr));
// This line initializes the server_addr structure (which holds address info)
by setting all its bytes to 0.
// without this line, the server_addr structure might contain random garbage
values in fields you’re not explicitly setting, and bind() might fall.
server_addr.sin_family = AF_INET; // IPv4
server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on any interface
server_addr.sin_port = htons(PORT); // Convert port number to
network byte order
// 3. Bind the socket to the specified IP and port
if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
{
perror("bind failed");
close(server_fd);
exit(EXIT_FAILURE);
}
/ 4. Listen for incoming connections
if (listen(server_fd, BACKLOG) < 0) {
perror("listen failed");
close(server_fd);
exit(EXIT_FAILURE);
}
printf("Server listening on port %d...\n", PORT);
// 5. Accept an incoming connection
addr_len = sizeof(client_addr);
client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
if (client_fd < 0) {
perror("accept failed");
close(server_fd);
exit(EXIT_FAILURE);
}
printf("Connection accepted from %s:%d\n",
inet_ntoa(client_addr.sin_addr),
// Converts the client’s IP address from binary to human-readable format
(e.g. "192.168.1.10").
ntohs(client_addr.sin_port));
//Converts the port number from network byte order to host byte order.
//Network order is big-endian (used across the internet).
//Your machine might be little-endian → this ensures the port is readable.
int stopTalking = 0;
// 6. Receive data from the client
num_bytes = recv(client_fd, buffer, BUFSIZE - 1, 0);
if (num_bytes < 0) {
perror("recv failed");
} else { buffer[num_bytes] = '\0'; // Null-terminate the received data
printf("Received: %s\n", buffer);
if(strcmp(buffer,"1") == 0)
{
strcpy(buffer, "1. Sign In\n 2. Create Account \n 3. Sign out");

//Search





}
else if (strcmp(buffer, "2") == 0)
{
strcpy(buffer, "Lets create you a sign in");





stopTalking = 1;
}
else
{
strcpy(buffer, "Invalid selection");
}
// 7. Echo the message back to the client
if (send(client_fd, buffer, sizeof(buffer), 0) < 0) {
perror("send failed");
}
}
// 8. Close the connections
close(client_fd); // Connected socket (used to talk to a specific client)
close(server_fd);// Listening socket (server waits here for clients)
return 0;
}
