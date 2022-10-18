#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

#define SEND_PACKAGE_SIZE 1024

void webserv::send_continue(const int index) {

	SocketInfo_s &socket = sockets_info[index];

	/* Send message in parts */

	static char buffer[SEND_PACKAGE_SIZE];
	int res = read(socket.send_fd, buffer, SEND_PACKAGE_SIZE);
	
	if (res == 0) {
		close(socket.send_fd);
		socket.recieving_from_server = false;
		if (socket.send_is_cgi)
			this->disconnect_socket(index);
		return;
	}
	
	if (res < 0)
		ft_error("send_continue");
	
	::send(sockets[index].fd, buffer, res, 0);
}
