#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

#define SEND_PACKAGE_SIZE 100

void webserv::send_continue(const int index) {

	SocketInfo_s &socket = sockets_info[index];

	/* Send message in parts */

	static char buffer[SEND_PACKAGE_SIZE + 1];
	int res = read(socket.send_fd, buffer, SEND_PACKAGE_SIZE);
	if (res < 0)
		ft_error("send_continue");
	::send(sockets[index].fd, buffer, res, 0);
	if (res < SEND_PACKAGE_SIZE - 1) {
		close(socket.send_fd);
		socket.recieving_from_server = false;
	}

	// if (socket.send_length_left <= 0) {
	// 	socket.recieving_from_server = false;
	// 	return;
	// }

	// long jump = std::min<long>(socket.send_length_left, SEND_PACKAGE_SIZE);
	// ::send(sockets[index].fd, socket.send_str_ptr, jump, 0);
	// socket.send_length_left -= SEND_PACKAGE_SIZE;
	// socket.send_str_ptr += jump;

}
