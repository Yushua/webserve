#include <webserv.hpp>
#include <iostream>
#include <colors.hpp>

void webserv::run() {

	int event_count = poll(sockets, SOCKET_COUNT_MAX, TIMEOUT);
	switch (event_count) {
		default: break;
		case  0: return; /* Skip; there are not events */
		case -1: ft_error("poll");exit(1); /* !!!ERROR!!! */
	}

	/* Handle connections */
	for (int index = 0; index < SOCKET_COUNT_MAX; index++) {

		/* References for easy access */
		short &events = sockets[index].revents;
		struct SocketInfo_s &socket = sockets_info[index];
		struct pollfd &poll_fd = sockets[index];

		/* Nothing to do */	
		if (poll_fd.fd == numeric_limits<int>::max() /* Is nothing */
			|| socket.fd_only                        /* Not a socket */
			|| !events)                              /* No events */
			continue;

		/* Disconnect connections with errors */	
		if (events & ~(POLLOUT | POLLIN))
			{ this->disconnect(index); continue; }

		/* There's something to send */
		if (socket.recieving_from_server
			&& events & POLLOUT
			&& (socket.send_fd_index == -1
				|| sockets[socket.send_fd_index].revents & POLLIN))
			{ this->send_continue(index); continue; }

		/* There's something to read */
		if (events & POLLIN && socket.msg.getState() != msgError) {

			if (availablePositions.size() < 2)
				continue;

			if (sockets_info[index].listen)
				this->connect_new_socket(index);
			else
				this->handle_request(index);
			continue;
		}
	}
}
