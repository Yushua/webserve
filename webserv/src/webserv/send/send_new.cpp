#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>
#include <colors.hpp>

void webserv::send_new(const int index, string headers, const int fd_index) {

	::send(sockets[index].fd, headers.c_str(), headers.length(), 0);

	if (sockets_info[index].recieving_from_server) {
		cout << RED << index << " Reciving new thing\n" << RESET;
		this->disconnect(sockets_info[index].send_fd_index);
	}
	else
		sockets_info[index].recieving_from_server = true;
	
	sockets_info[index].send_fd_index = fd_index;
	sockets_info[index].disconnect_after_send = false;

#ifdef DEBUG
	cout << MAGENTA << "  -~={ " << index << " is recieving this }=~-\n" << RESET;
	cout << headers;
#endif
}
