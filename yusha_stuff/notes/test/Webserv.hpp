#ifndef WEBSERV
	#define WEBSERV

#include "header.hpp"

class Webserv 
{
    private:
        struct pollfd tmp;//make it more
    public:
        Webserv(int port);
        ~Webserv();
        int run();
};

#endif
