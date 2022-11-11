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
#include <dirent.h>

#include <string>
#include <map>
#include <stack>
#include <limits>

using namespace std;

#include <cstdlib>
#include <ft_lib.hpp>
#include <message.hpp>

typedef int socket_t;

#define KILOBYTE 1000
#define MEGABYTE 1000000
#define GIGABYTE 1000000000

#define TIMEOUT 100000
#define SOCKET_COUNT_MAX 250

struct SocketInfo_s {
	message msg;
	bool fd_only;
	bool listen;
	struct sockaddr_in address;
	int addrlen;
	bool recieving_from_server;
	int send_fd_index;
	string send_headers;
	bool disconnect_after_send;
};

#include <config_struct.hpp>

class webserv {
private:

	void handle_request(const int index);

	/* Socket information */
		struct pollfd *sockets;
		struct SocketInfo_s *sockets_info;

	/* PollArray position managment */
		stack<int> availablePositions;
		int tryGetAvailablePosition();
		void returnPosition(int position);

	/* Connections */
		int connect_new_fd_only(const int index, const int fd);
		int connect_new_socket(const int index);
		void disconnect(const int index);

	/* Send */
		int send_new(const int index, string headers, const int fd);
		void send_new_file(const int index, string headers, const string path);
		void send_new_error(const int index, const int error_code);
		void send_new_error_fatal(const int index, const int error_code);

		void send_continue(int index);

	/* CGI */
		void cgi_get(const int index, const message &msg, const string &requested_file, const string &interpreter);
		void cgi_post(const int index, const message &msg, const string &requested_file, const string &interpreter, std::string boundary);
		void cgi_post_nb(int *input_pipe, int *output_pip, std::string send, const int index, const message &msg, const string &requested_file, const string &interpreter);

	/* Utils */
		bool make_sure_messege_is_complete(const int index);
		const string header_get_content_type(const string filename);
		int generate_index_page(const int index, const message &msg);

public:

	webserv();
	~webserv();

	void run();

	/* Config Default */
		map<string, string> cgi_options;
		map<int, string> error_pages;

		void config_listen_to_port(const unsigned port, int line);
		void config_listen_to_port(const string port, int line);
		void config_add_cgi_option(const string extension, const string interpreter_path, int line);
		void config_add_error_page(const unsigned int error, const string page_path, int line);
		void config_add_error_page(const string error, const string page_path, int line);
	
	/* Config Redirect */
		struct Config_s default_config;
		map<string, struct Config_s> configs;

		void config_new_redirect(string redirect_from, string redirect_to, int line);
		void config_set_body_size(string redirect_from, const string &str, int line);
		void config_add_method(string redirect_from, const string &method, int line);
		void config_set_dir_behavior(string redirect_from, const string &behavior, int line);

	/* HTTP Methods */
		void cmd_GET(const int index, const message &msg);
		void cmd_HEAD(const int index, const message &msg);
		void cmd_POST(const int index, message &msg); /* !!!TO BE IMPLEMENETD!!! */
		void plainText(const int index, message &msg);
		void cmd_DELETE(const int index, const message &msg); /* !!!TO BE IMPLEMENETD!!! */

	static void debug_print_request(const int index, message &msg);
};
void configParser(map<string, webserv*> &bigacontyantnas, std::string path_config);

#endif
