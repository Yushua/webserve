#include <webserv.hpp>

int main() {
	webserv server;
	server.config_listen_to_port(4242);
	server.config_listen_to_port(4243);
	server.config_add_cgi_option("py", "/Users/rdrazsky/.brew/bin/python3");
	server.config_add_cgi_option("lol", "");
	server.run();
}
