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


#define PORT 4234
#define READ_BUFFER_SIZE 4242

//figure otu closing ports mistake with 4242
int main(void)
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
 
    // Creating socket file descriptor
    //listens will be the socket, the bound  specified in the config file
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
    struct pollfd tmp;
	tmp.fd = new_socket;
	tmp.events = POLLIN;
	tmp.revents = 0;
    char buffer[1024] = { 0 };
    std::string hello = "";
    int size = 1;
    std::cout << "start server" << std::endl;
    while (1)
    {
        poll(&tmp, 1, 1);
        //maybe place which client joined here
        if (tmp.revents == POLLIN)
        {
            hello.clear();
            // size = read(tmp.fd, tmpString, READ_BUFFER_SIZE);
            while(true)
            {
                printf("startsize = %i\n", size);
                char temp_buffer[READ_BUFFER_SIZE + 1];
                size = read(tmp.fd, temp_buffer, READ_BUFFER_SIZE);
                if (size <= 0)
                    break;
                temp_buffer[size] = '\0';
                hello += temp_buffer;
                std::cout << hello << std::endl;
            }
            if (hello == "END")
                break;
            // std::getline(std::cin, hello);
            // // std::cout << hello << std::endl;
            // std::cout << "print message:" << hello << std::endl;
            // printf("[%s]\n", hello.c_str());
            // send(new_socket, hello.c_str(), hello.length(), 0);
        }
    }
 
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
