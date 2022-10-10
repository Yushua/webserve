#include <webserv.hpp>

int main() {
	//loop
	// map<std::string, webserv> neverOvererlyRedundantMaliciousArdousLesson;
	// configParser(neverOvererlyRedundantMaliciousArdousLesson);//normal name

	webserv server;
	server.config_listen_to_port("4242");
	server.config_listen_to_port("4243");
	server.config_add_cgi_option("py", "/usr/bin/python");
	server.config_add_cgi_option("lol", "");
	while (true)
		server.run();
}
