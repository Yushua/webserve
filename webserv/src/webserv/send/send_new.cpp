#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>
#include <colors.hpp>

int webserv::send_new(const int index, string headers, const int fd) {

	int fd_position;
	if (fd == -1)
		fd_position = -1;
	else {
		fd_position = this->connect_new_fd_only(index, fd);
		if (fd_position == -1) {
			cout << RED << "FUCK\n" << RESET;
			exit(1);
		}
	}

	sockets_info[index].send_headers = headers;

	if (sockets_info[index].recieving_from_server) {
		cout << RED << index << " Reciving new thing\n" << RESET;
		this->disconnect(sockets_info[index].send_fd_index);
	}
	else
		sockets_info[index].recieving_from_server = true;
	
	sockets_info[index].send_fd_index = fd_position;
	sockets_info[index].disconnect_after_send = false;

	return fd_position;

#ifdef DEBUG
	cout << MAGENTA << "  -~={ " << index << " is recieving this }=~-\n" << RESET;
	cout << headers;
#endif
}
