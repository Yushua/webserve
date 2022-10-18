#include <webserv.hpp>
#include <iostream>

void webserv::run()
{
	/* Update socket count */
	socket_count = new_socket_count;

	int event_count = poll(sockets, 1 + socket_count, TIMEOUT);
	switch (event_count) {
		default: break;
		case  0: return; /* Skip; there are not events */
		case -1: perror("poll");exit(1); /* !!!ERROR!!! */
	}

	/* Handle connections */
	for (int index = 0; index <= socket_count; index++) {
		short events = sockets[index].revents;
		
		/* Nothing to do */	
		if (!events) continue;
		
		/* There's something to read */
		if (events & POLLIN) {
			if (sockets_info[index].listen)
					/* Handle new connection */
					this->connect_new_socket(index);
				else
					/* Handle new request */
					this->handle_request(index);
				continue;
		}

		/* There's something to send */
		if (sockets_info[index].recieving_from_server
			&& events & POLLOUT) {
			this->send_continue(index);
			continue;
		}
	}
}
