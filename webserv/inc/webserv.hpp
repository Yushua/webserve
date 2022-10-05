#ifndef WEBSERV_HPP
	#define WEBSERV_HPP

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
#include <map>

using namespace std;

#include <ft_lib.hpp>
#include <message.hpp>

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
	void handle_request(const int index);
	void disconnect_socket(const int index);

	void send(const int fd, const string msg);
	void send_error(const int fd, const int error_code);

	const string header_get_content_type(const string filename);

	void cgi_get(const int fd, const message &msg, const string &requested_file);

public:
	webserv(int port);
	~webserv();

	void run();

	void cmd_GET(const int index, const message &msg);
	void cmd_HEAD(const int index, const message &msg);
	void cmd_POST(const int index, const message &msg); /* !!!TO BE IMPLEMENETD!!! */
	void cmd_DELETE(const int index, const message &msg); /* !!!TO BE IMPLEMENETD!!! */
};


#endif
