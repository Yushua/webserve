#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>

#define SEND_PACKAGE_SIZE 1024

void webserv::send(const int fd, const string msg) {

	/* This code makes me wanna cry; please fix */

	long length_left = msg.length();
	long length_sent = 0;
	const char *str = msg.c_str();

	long jump = 0;
	while (length_left > 0)
	{
		if (length_left > SEND_PACKAGE_SIZE)
			jump = SEND_PACKAGE_SIZE;
		else
			jump = length_left;

		// write(1, str, jump);
		::send(fd, str, jump, 0);
		length_left -= SEND_PACKAGE_SIZE;
		length_sent += jump;
		str += jump;
	}
	(void)fd;
	
	// ::send(fd, msg.c_str(), msg.length(), 0);

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
