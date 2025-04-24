#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080 // Port number to connect to
#define BUFSIZE 1024 // Buffer size for data
int main(int argc, char * argv[]) {
int menu()
{
printf("Asking the server for more information\n");
printf("Type either 1 or 2 depending on your wanted consiquence\n");
printf("1. Continue\n");
printf("2. Sign Out\n");

int choice;
scanf("%d", &choice);
return choice;
}
int sock_fd;
struct sockaddr_in server_addr;
char buffer[BUFSIZE] = "Hello, server!";
int num_bytes;
set parameter
if (argc != 3)
{
printf("Usage: %s IP-address port-number", argv[0]);
return 0;
}
int port = atoi(argv[2]);
/
// 1. Create a socket
sock_fd = socket(AF_INET, SOCK_STREAM, 0);
if (sock_fd < 0) {
perror("socket failed");
exit(EXIT_FAILURE);
}// 2. Set up the server address structure
memset(&server_addr, 0, sizeof(server_addr)); // Clear structure
server_addr.sin_family = AF_INET; // IPv4
server_addr.sin_port = htons(PORT); // Server port in network byte
order
// Convert the IP address from text to binary form. Here we assume server is
localhost.
if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
perror("inet_pton failed");
close(sock_fd);
exit(EXIT_FAILURE);
}
// 3. Connect to the server
if (connect(sock_fd, (struct sockaddr)&server_addr, sizeof(server_addr)) < 0)
{
perror("connect failed");
close(sock_fd);
exit(EXIT_FAILURE);
}
while(1)
{
int choice = menu();
int status = sprintf(buffer, "%d", choice);
// 4. Send a message to the server
if (send(sock_fd, buffer, strlen(buffer), 0) < 0) {
perror("send failed");
close(sock_fd);
exit(EXIT_FAILURE);
}
// 5. Receive the echo from the server
num_bytes = recv(sock_fd, buffer, BUFSIZE - 1, 0);
if (num_bytes < 0) {
perror("recv failed");
} else {
//buffer[num_bytes] = '\0'; // Null-terminate the data received
printf("Reply from server: %s\n", buffer);
if(choice = 2)
{

break;
}
}
}
// 6. Close the socket
close(sock_fd);
return 0;
}
>>>>>>> Stashed changes
