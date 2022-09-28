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

#include "Webserv.hpp"

//figure otu closing ports mistake with 4242

Webserv::Webserv(int port)
{
 
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
    //multiple sockets, to get multiple clients
    // tmp = new(struct pollfd);
}

Webserv::~Webserv()
{}

std::string page1 = "HTTP/1.1 200 OK\n\n\
<!DOCTYPE html><html><body>\n\
<h1>Welcome!</h1>\n\
<p>This is my server!</p>\n\
<a href=\"lol\">Go somewhere far beyond!</a>\n\
</body></html>";

void Webserv::impliment_socket(void)
{
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    tmp.fd = new_socket;
	tmp.events = POLLIN;
	tmp.revents = 0;
    fcntl(new_socket, F_SETFL, O_NONBLOCK);
}

int Webserv::run(void)
{
    char buffer[1024] = { 0 };
    std::string hello = "";
    std::cout << "start server" << std::endl;
    while (1)
    {
        poll(&tmp, 1, 1);
        //maybe place which client joined here
        if (tmp.revents == POLLIN)
        {
            hello.clear();
            while(true)
            {
                char temp_buffer[READ_BUFFER_SIZE + 1];
                int size;
                size = read(tmp.fd, temp_buffer, READ_BUFFER_SIZE);//why wait, just give me an end of file?
                if (size <= 0)
                    break;
                temp_buffer[size] = '\0';
                hello += temp_buffer;
            }
            std::cout << hello << '\n';
            if (hello == "END")
                break;
        }
    }
    return 0;
}
