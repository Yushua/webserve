#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

void webserv::send_continue(int index) {

	SocketInfo_s *socket = &(sockets_info[index]);
	pollfd *poll_file = &(sockets[socket->send_fd_index]);
	string *send_headers = &(socket->send_headers);

	/* Send message in parts */

	if (send_headers->size() > 0) {
		if (write(sockets[index].fd, send_headers->c_str(), send_headers->length()) == -1)
			this->disconnect(index);
		send_headers->clear();
		if (socket->send_fd_index == -1) {
			socket->recieving_from_server = false;
			if (socket->disconnect_after_send)
				this->disconnect(index);
		}
		return;
	}

	static char buffer[PIPE_BUF];
	int ret = read(poll_file->fd, buffer, PIPE_BUF);

	if (ret == -1)
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

	if (write(sockets[index].fd, buffer, ret) == -1)
		this->disconnect(index);
}
