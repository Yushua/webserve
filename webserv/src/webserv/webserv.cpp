#include <webserv.hpp>

webserv::webserv() {
	socket_count = 0; /* Number of conected sockets */
	new_socket_count = 0; /* Used to update the variable above */

	/* Array of all sockets for poll */
	sockets = new struct pollfd[SOCKET_COUNT_MAX];
	sockets_info = new struct SocketInfo_s[SOCKET_COUNT_MAX];
}

webserv::~webserv() {
	delete [] sockets;
	delete [] sockets_info;
}
