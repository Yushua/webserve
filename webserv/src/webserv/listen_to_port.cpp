#include <webserv.hpp>
#include <colors.hpp>

void webserv::listen_to_port(int port) {
	try {
		/* code */
		socket_t new_welcome_socket;
		struct sockaddr_in address;
		int addrlen;

		/* Setting up address struct */
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(port);
		addrlen = sizeof(address);

		{/* Initialize main server socket */
			/* Make a new socket */
			new_welcome_socket = socket(AF_INET, SOCK_STREAM, 0);
			if (new_welcome_socket < 0)
				throw "socket";
			
			/* Setting socket flags */
			int opt = 1;
			if (setsockopt(new_welcome_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
				close(new_welcome_socket);
				throw "setsockopt";
			}
			
			/* Attach address (and port) to main socket */
			if (::bind(new_welcome_socket, (struct sockaddr *)&address, sizeof(address))) {
				close(new_welcome_socket);
				throw "bind";
			}
			
			/* Make socket listen for new connections */
			if (listen(new_welcome_socket, 3)) {
				close(new_welcome_socket);
				throw "listen";
			}
		}

		/* Adding the main socket to the array */
		/* This socket will always be on possition 0 */
		sockets[new_socket_count].fd = new_welcome_socket;
		sockets[new_socket_count].events = POLLIN;
		sockets[new_socket_count].revents = 0;
		sockets_info[new_socket_count].listen = true;
		sockets_info[new_socket_count].address = address;
		sockets_info[new_socket_count].addrlen = addrlen;
		fcntl(new_welcome_socket, F_SETFL, O_NONBLOCK);
#ifdef DEBUG
		std::cerr << GREEN << "  -~={ " << new_socket_count << " is listening to port " << port << " }=~-\n" << RESET;	
#endif
		++new_socket_count;
	}
	catch(const char *error) {
		std::cerr << RED << "  -~={ Can't listen to port " << port << ", because of a " << error << " error }=~-\n" << RESET;
	}
}
