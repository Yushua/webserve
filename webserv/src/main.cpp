#include <webserv.hpp>

int main() {
	webserv server;
	server.listen_to_port(4242);
	server.listen_to_port(4243);
	server.run();
}
