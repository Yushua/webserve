#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>
#include <colors.hpp>

int webserv::send_new(const int index, string headers, const int fd) {

	/* Get poll position for new fd */
	int fd_position;
	if (fd == -1)
		fd_position = -1;
	else {
		fd_position = this->connect_new_fd_only(index, fd);
		if (fd_position == -1) {
			cout << RED << "FUCK" << RESET << '\n';
			exit(1);
		}
	}

	sockets_info[index].send_headers = headers;

	/* If client was already reciving something, replace it */
	if (sockets_info[index].recieving_from_server
		&& sockets_info[index].send_fd_index != -1) {
			this->disconnect(sockets_info[index].send_fd_index);
#ifdef DEBUG
			cout << RED << index << " Reciving new thing" << RESET << '\n';
#endif
	}
	else
		sockets_info[index].recieving_from_server = true;
	
	sockets_info[index].send_fd_index = fd_position;
	sockets_info[index].disconnect_after_send = false;

#ifdef DEBUG
	cout << MAGENTA << "  -~={ " << index << " is recieving this }=~-" << RESET << '\n';
	cout << headers;
#endif

	return fd_position;
}
