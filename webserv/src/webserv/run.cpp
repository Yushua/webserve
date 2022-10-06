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

		/* Handle connections */
		string read_buffer;
		for (int index = 0; index <= socket_count; index++) {
			switch (sockets[index].revents) {

				/* Nothing to do */
				case 0:
					continue;
				
				/* There's something to read */
				case POLLIN:
					if (sockets_info[index].listen)
						this->connect_new_socket(index); /* Handle new connection */
					else
						this->handle_request(index); /* Handle new request */
					continue;
				
				/* Error; disconnect! */
				default:
					this->disconnect_socket(index);
					continue;
			}
		}
	}
}
