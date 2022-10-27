#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

// #undef PIPE_BUF
// #define PIPE_BUF 1

void webserv::send_continue(int index) {

	SocketInfo_s *socket = &(sockets_info[index]);
	pollfd *poll_file = &(sockets[socket->send_fd_index]);

	// if (!(ft_cheeky_poll(poll_file->fd) & POLLIN))
	// 	return;
	// if (!(ft_cheeky_poll(sockets[index].fd) & POLLOUT))
	// 	return;

	/* Send message in parts */

	// Not sure wich buffer is ideal, try experimenting!
	// SO_SNDBUF PIPE_BUF
	static char buffer[PIPE_BUF];
	int ret = read(poll_file->fd, buffer, PIPE_BUF);

	if (ret < 0)
		ft_error("send_continue");

	if (ret == 0) {
		this->disconnect(socket->send_fd_index);
		socket->send_fd_index = -1;
		socket->recieving_from_server = false;
		socket->msg.reset();
		if (socket->disconnect_after_send)
			this->disconnect(index);
		return;
	}

	// ::send(sockets[index].fd, buffer, ret, MSG_OOB);
	::write(sockets[index].fd, buffer, ret);
}
