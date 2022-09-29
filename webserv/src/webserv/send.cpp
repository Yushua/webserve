#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>


void webserv::send(const int fd, const string msg)
{
	::send(fd, msg.c_str(), msg.length(), 0);

#ifdef DEBUG
	/* Print response without body */
	string msg_without_body = "";
	
	int nl = 0;
	for (size_t i = 0; i < msg.length(); i++) {
		if (msg[i] == '\n')
			nl++;
		else
			nl = 0;
		if (nl == 2) {
			msg_without_body = msg.substr(0, i - 1);
			break;
		}
	}
	
	cout << MAGENTA << "  -~={ Responded with }=~- \n" << RESET << msg_without_body << '\n';
#endif
}
