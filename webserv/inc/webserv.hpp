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

#include <cstdlib>
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
	bool recieving_from_server;
	int send_fd;
	bool send_is_cgi;
};

#include <config_struct.hpp>

class webserv {
private:

	int socket_count; /* Number of conected sockets */
	int new_socket_count; /* Used to update the variable above */

	struct pollfd *sockets;
	struct SocketInfo_s *sockets_info;

	void connect_new_socket(const int index);
	void handle_request(const int index);
	void disconnect_socket(const int index);

	void send_new(const int index, string headers, const int fd);
	void send_new_file(const int index, string headers, const string path);
	void send_new_error(const int index, const int error_code);

	void send_continue(const int index);

	const string header_get_content_type(const string filename);

	void cgi_get(const int index, const message &msg, const string &requested_file, const string &interpreter);

public: /* DELETE THIS LINE ONCE READING THE CONFIG FILE IS IMPLEMENTED */

	/* Global config stuff */
		map<string, string> cgi_options;
		map<int, string> error_pages;
	/* Local config stuff */
		struct Config_s default_config;
		map<string, struct Config_s> configs;

	static void debug_print_request(const int index, message &msg);

public:
	webserv();
	~webserv();

	void config_listen_to_port(const unsigned port);
	void config_listen_to_port(const string port);
	void config_add_cgi_option(const string extension, const string interpreter_path);
	void config_add_error_page(const unsigned int error, const string page_path);
	void config_add_error_page(const string error, const string page_path);

	void config_new_redirect(string redirect_from, string redirect_to);
	void config_set_body_size(string redirect_from, const string &str);
	void config_add_method(string redirect_from, const string &method);
	void config_set_dir_behavior(string redirect_from, const string &behavior);

	void run();

	void cmd_GET(const int index, const message &msg);
	void cmd_HEAD(const int index, const message &msg);
	void cmd_POST(const int index, const message &msg); /* !!!TO BE IMPLEMENETD!!! */
	void cmd_DELETE(const int index, const message &msg); /* !!!TO BE IMPLEMENETD!!! */
};

#endif
