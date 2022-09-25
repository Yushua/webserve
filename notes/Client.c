#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
 
int main(int argc, char const* argv[])
{
    int sock = 0, valread, client_fd;
    if (argc == 1)
    {
        return (0);
    }
    char* name = argv[1];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((client_fd
         = connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    char buffer[1024] = { 0 };
    struct pollfd;
    {
        int   fd  = sock;         /* file descriptor */
        short events;     /* requested events */
    };
    std::string string;
    while (1)
    {
        send(sock, hello, strlen(hello), 0);
        printf("%s: Hello message sent\n" name);
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
    }
    // closing the connected socket
    close(client_fd);
    return 0;
}
