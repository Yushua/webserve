#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>
#include <iostream>

#define PORT 4242
 
int main(void)
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
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
    std::string hello = "";
    while(1)
    {
        hello.clear();
        std::getline(std::cin, hello);
        if (hello == "END")
            break;
        send(sock, hello.c_str(), hello.length(), 0);
    }
    close(client_fd);
    close(sock);
    exit(1);
    return 0;
}
