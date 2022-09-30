#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

#define SEND_PACKAGE_SIZE 1024

void webserv::send(const int fd, const string msg) {

	/* Send message in parts */

	long length_left = msg.length();
	const char *str_ptr = msg.c_str();

	long jump = 0;
	while (length_left > 0) {
		jump = std::min<long>(length_left, SEND_PACKAGE_SIZE);
		::send(fd, str_ptr, jump, 0);
		length_left -= SEND_PACKAGE_SIZE;
		str_ptr += jump;
	}

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
