#include <webserv.hpp>
#include <colors.hpp>

void webserv::config_listen_to_port(const unsigned int port, int line) {
	if (port < 0 || port > 65535) {
		std::cerr << RED << "  -~={ line " << line << ": Invalid port number " << port << " }=~-\n" << RESET;
		exit(1);
	}
	
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

		/* Adding the new listen socket to the array */
		int position = this->tryGetAvailablePosition();
		if (position == -1) {
			cerr << RED << "  -~={ Can't add more listen sockets! }=~-\n" << RESET;
			exit(1);
		}
		sockets[position].fd = new_welcome_socket;
		sockets[position].events = POLLIN;
		sockets[position].revents = 0;
		sockets_info[position].listen = true;
		sockets_info[position].address = address;
		sockets_info[position].addrlen = addrlen;
		fcntl(new_welcome_socket, F_SETFL, O_NONBLOCK);
#ifdef DEBUG
		std::cout << GREEN << "  -~={ " << position << " is listening to port " << port << " }=~-\n" << RESET;	
#endif
	}
	catch(const char *error) {
		std::cerr << RED << "  -~={ line " << line << ": Can't listen to port " << port << ", because of a " << error << " error }=~-\n" << RESET;
		exit(1);
	}
}

void webserv::config_listen_to_port(const string port, int line) {
	if (port == "" || port.find_first_not_of("0123456789") != string::npos) {
		std::cerr << RED << "  -~={ line " << line << ": Invalid port number " << port << " }=~-\n" << RESET;
		exit(1);
	}
	config_listen_to_port(atoi(port.c_str()), line);
}
