#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sstream>

void webserv::cmd_GET(const int index, const message &msg) {
	
	/* BAD CODE, please fix */

	const vector<string> startLine = msg.getStartLine();
	const map<string, string> headers = msg.getHeaders();
	const string body = msg.getBody();

	string root = "root";
	string requested_file = root + msg.getStartLine()[1];
	if (requested_file == "root/")
		 requested_file = "root/index.html";

	ifstream file;
	file.open(requested_file.c_str());
	stringstream buffer;
	buffer << file.rdbuf();

	string ok = "HTTP/1.1 200 OK\n";
	ok += this->header_get_content_type(requested_file);
	ok += "Content-length: " + to_string((buffer.str().length())) + '\n';
	ok += "\n" + buffer.str();
	this->send(sockets[index].fd, ok);
}
