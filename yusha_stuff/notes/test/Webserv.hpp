#ifndef WEBSERV
	#define WEBSERV

#include "header.hpp"

class Webserv 
{
    private:
        struct pollfd tmp;//make it more
        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
    public:
        Webserv(int port);
        ~Webserv();
        int run();
        void impliment_socket();
};

#endif
