#include <webserv.hpp>

webserv::webserv() {

	/* Array of all sockets for poll and another for aditional information */
	sockets = new struct pollfd[SOCKET_COUNT_MAX];
	sockets_info = new struct SocketInfo_s[SOCKET_COUNT_MAX];

	for (size_t i = 0; i < SOCKET_COUNT_MAX; i++) {
		sockets[i].fd = numeric_limits<int>::max();
		sockets[i].events = POLLIN | POLLOUT;
		sockets[i].revents = 0;
		this->returnPosition(i);
	}
}

webserv::~webserv() {
	delete [] sockets;
	delete [] sockets_info;
}
