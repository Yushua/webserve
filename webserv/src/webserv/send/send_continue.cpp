#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

void webserv::send_continue(int index) {

	SocketInfo_s *socket = &(sockets_info[index]);
	pollfd *poll_file = &(sockets[socket->send_fd_index]);

	/* Send message in parts */

	// Not sure wich buffer is ideal, try experimenting!
	// SO_SNDBUF PIPE_BUF
	static char buffer[PIPE_BUF];
	int ret = read(poll_file->fd, buffer, PIPE_BUF);

	if (ret < 0)
		{ this->disconnect(index); return; }

	if (ret == 0) {
		this->disconnect(socket->send_fd_index);
		socket->send_fd_index = -1;
		socket->recieving_from_server = false;
		socket->msg.reset();
		if (socket->disconnect_after_send)
			this->disconnect(index);
		return;
	}

	::write(sockets[index].fd, buffer, ret);
}
