/**
 * @file Server.c
 * @author (yushabakker1@gmail.com)
 * @brief https://www.geeksforgeeks.org/socket-programming-cc/
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

#include <string>
#include <iostream>


#define PORT 4232

//figure otu closing ports mistake with 4242
int main(void)
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    // Forcefully attaching socket to the port 8080
    printf("4\n");
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("wait for client\n");
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("6\n");
    struct pollfd tmp;
	tmp.fd = new_socket;
	tmp.events = POLLIN;
	tmp.revents = 0;
    char buffer[1024] = { 0 };
    std::string hello = "";
    while (1)
    {
        poll(&tmp, 1, 1);
        std::cout << tmp.revents << std::endl;
        if (tmp.revents != 0)
        {
            hello.clear();
            std::getline(std::cin, hello);
            std::cout << hello << std::endl;
            if (hello == "END")
                break;
            send(new_socket, hello.c_str(), hello.length(), 0);
        }
    }
 
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
