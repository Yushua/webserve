#include <webserv.hpp>

webserv::webserv(int port)
{
	/* Setting up address struct */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	addrlen = sizeof(address);

	{/* Initialize main server socket */
		/* Make a new socket */
		welcome_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (welcome_socket < 0)
			error("socket");
		
		/* Setting socket flags */
		int opt = 1;
		if (setsockopt(welcome_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
			error("setsockopt");
		
		/* Attach address (and port) to main socket */
		if (::bind(welcome_socket, (struct sockaddr *)&address, sizeof(address)))
			error("bind");
		
		/* Make socket listen for new connections */
		if (listen(welcome_socket, 3))
			error("listen");
	}

	socket_count = 0; /* Number of conected sockets */
	new_socket_count = 0; /* Used to update the variable above */

	/* Array of all sockets for poll */
	sockets = new struct pollfd[SOCKET_COUNT_MAX];

	/* Adding the main socket to the array */
	/* This socket will always be on possition 0 */
	sockets[0].fd = welcome_socket;
	sockets[0].events = POLLIN;
	sockets[0].revents = 0;
	fcntl(welcome_socket, F_SETFL, O_NONBLOCK);
}

webserv::~webserv() {
	delete [] sockets;
}
