#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>


void webserv::send(const int fd, const string msg)
{
#ifdef DEBUG
	cout << MAGENTA << "  -~={ Responded with }=~- \n" << RESET << msg << '\n';
#endif
	
	::send(fd, msg.c_str(), msg.length(), 0);
}
