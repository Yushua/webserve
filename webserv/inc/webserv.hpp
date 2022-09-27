#ifndef WEVSERVE_HPP
	#define WEVSERVE_HPP

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#include <poll.h>
#include <fcntl.h>

#include <string>

using namespace std;

#include <error.hpp>

typedef int socket_t;

#define TIMEOUT 3*60*1000
#define READ_BUFFER_SIZE 1024

#define SOCKET_COUNT_MAX 100

class webserv {
private:
	socket_t welcome_socket;
	struct sockaddr_in address;
	int addrlen;

	int socket_count; /* Number of conected sockets */
	int new_socket_count; /* Used to update the variable above */

	struct pollfd *sockets;

	void connect_new_socket();
	void handle_request(int index);
	void disconnect_socket(int index);

	void send(const int fd, const string msg);

public:
	webserv(int port);
	~webserv();

	void run();
};

#endif
