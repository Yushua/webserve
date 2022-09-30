#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sstream>

void webserv::cmd_GET(const int index, const message &msg) {

	/* ??????? Maybe try differentiating between files and dirs ??????? */

	string requested_file = msg.getStartLine()[1];
	if (requested_file == "/")
		 requested_file = "/index.html";

	ifstream file("root" + requested_file);

	if (!file.good()) {
		this->send_error(sockets[index].fd, 404);
		this->disconnect_socket(index);
		return;
	}

	cout << file.good() << '\n';
	stringstream buffer;
	buffer << file.rdbuf();

	string ok = "HTTP/1.1 200 OK\n";
	ok += this->header_get_content_type(requested_file);
	ok += "Content-length: " + ft_to_string((buffer.str().length())) + '\n';
	ok += "\n" + buffer.str();
	this->send(sockets[index].fd, ok);
}
