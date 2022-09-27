#include <webserv.hpp>
#include <iostream>

void webserv::run()
{
	while (true) {
		/* Update socket count */
		socket_count = new_socket_count;

		int event_count = poll(sockets, 1 + socket_count, TIMEOUT);
		switch (event_count) {
			default: break;
			case  0: continue; /* Skip; there are not events */
			case -1: perror("poll");exit(1); /* !!!ERROR!!! */
		}

		/* Check for new connections */
		if (sockets[0].revents == POLLIN)
			this->connect_new_socket();

		/* Handle connections */
		string read_buffer;
		for (int index = 1; index <= socket_count; index++) {
			switch (sockets[index].revents) {

				/* Nothing to do */
				case 0:
					continue;
				
				/* There's something to read */
				case POLLIN:
					this->handle_request(index); continue;
				
				/* Error; disconnect! */
				default:
					this->disconnect_socket(index); continue;
			}
		}
	}
}
