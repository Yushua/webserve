#ifndef WEBSERV_HPP
	#define WEBSERV_HPP

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
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

#define SOCKET_COUNT_MAX 250

struct SocketInfo_s {
	bool listen;
	struct sockaddr_in address;
	int addrlen;
};

struct Config_s {
	string redirect_path;
	map<string, bool> allowed_methods;
	size_t client_body_size;
	string dir_behavior;
};

class webserv {
private:

	int socket_count; /* Number of conected sockets */
	int new_socket_count; /* Used to update the variable above */

	struct pollfd *sockets;
	struct SocketInfo_s *sockets_info;

	void connect_new_socket(const int index);
	void handle_request(const int index);
	void disconnect_socket(const int index);

	void send(const int index, const string msg);
	void send_error(const int index, const int error_code);

	const string header_get_content_type(const string filename);

	void cgi_get(const int index, const message &msg, const string &requested_file, const string &interpreter);

	/* Global config stuff */
		map<string, string> cgi_options;
		map<int, string> error_pages;
	/* Local config stuff */
		struct Config_s default_config;
		map<string, Config_s> configs;

public:
	webserv();
	~webserv();

	void config_listen_to_port(const int port);
	void config_add_cgi_option(const string extension, const string interpreter_path);
	void config_add_error_page(const int error, const string page_path);

	void run();

	void cmd_GET(const int index, const message &msg);
	void cmd_HEAD(const int index, const message &msg);
	void cmd_POST(const int index, const message &msg); /* !!!TO BE IMPLEMENETD!!! */
	void cmd_DELETE(const int index, const message &msg); /* !!!TO BE IMPLEMENETD!!! */
};

#endif
