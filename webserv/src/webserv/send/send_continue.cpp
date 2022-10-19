#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

void webserv::send_continue(const int index) {

	SocketInfo_s &socket = sockets_info[index];

	/* Send message in parts */

	// Not sure wich buffer is ideal, try experimenting!
	// SO_SNDBUF PIPE_BUF
	static char buffer[PIPE_BUF];
	int res = read(socket.send_fd, buffer, PIPE_BUF);
	
	if (res == 0) {
		close(socket.send_fd);
		socket.recieving_from_server = false;
		if (socket.disconnect_after_send)
			this->disconnect_socket(index);
		return;
	}
	
	if (res < 0)
		ft_error("send_continue");
	
	::send(sockets[index].fd, buffer, res, 0);
}
