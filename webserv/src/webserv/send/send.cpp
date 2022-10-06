#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

#define SEND_PACKAGE_SIZE 1024

void webserv::send(const int index, const string msg) {

	/* Send message in parts */

	long length_left = msg.length();
	const char *str_ptr = msg.c_str();

	long jump = 0;
	while (length_left > 0) {
		jump = std::min<long>(length_left, SEND_PACKAGE_SIZE);
		::send(sockets[index].fd, str_ptr, jump, 0);
		length_left -= SEND_PACKAGE_SIZE;
		str_ptr += jump;
	}

#ifdef DEBUG
	string stripped_msg = "";
	/* Print response without body */
	int nl = 0;
	for (size_t i = 0; i < msg.length(); i++) {
		if (msg[i] == '\n')
			nl++;
		else
			nl = 0;
		if (nl == 2) {
			stripped_msg = msg.substr(0, i - 1);
			break;
		}
	}
	cout << MAGENTA << "  -~={ " << index << " was sent this }=~- \n" << RESET << stripped_msg << '\n';
#endif
}
