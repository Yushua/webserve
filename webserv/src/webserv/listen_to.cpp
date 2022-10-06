#include <webserv.hpp>

void webserv::listen_to_port(int port) {
	socket_t welcome_socket;
	struct sockaddr_in address;
	int addrlen;

	/* Setting up address struct */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	addrlen = sizeof(address);

	{/* Initialize main server socket */
		/* Make a new socket */
		welcome_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (welcome_socket < 0)
			ft_error("socket");
		
		/* Setting socket flags */
		int opt = 1;
		if (setsockopt(welcome_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
			ft_error("setsockopt");
		
		/* Attach address (and port) to main socket */
		if (::bind(welcome_socket, (struct sockaddr *)&address, sizeof(address)))
			ft_error("bind");
		
		/* Make socket listen for new connections */
		if (listen(welcome_socket, 3))
			ft_error("listen");
	}

	/* Adding the main socket to the array */
	/* This socket will always be on possition 0 */
	sockets[new_socket_count].fd = welcome_socket;
	sockets[new_socket_count].events = POLLIN;
	sockets[new_socket_count].revents = 0;
	sockets_info[new_socket_count].listen = true;
	sockets_info[new_socket_count].address = address;
	sockets_info[new_socket_count].addrlen = addrlen;
	fcntl(welcome_socket, F_SETFL, O_NONBLOCK);
	++new_socket_count;
}
