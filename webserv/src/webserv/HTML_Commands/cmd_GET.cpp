#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void webserv::cmd_GET(const int index, const message &msg) {

	/* ??????? Maybe try differentiating between files and dirs ??????? */

	string requested_file = msg.getStartLine()[1];
	if (requested_file == "/")
		 requested_file = "/index.html";

	/* Try openign file in root */
	ifstream file("root" + requested_file);

	/* Check if path exists */
	if (!file.good()) {
		this->send_error(sockets[index].fd, 404);
		this->disconnect_socket(index);
		return;
	}

	/* Read file */
	cout << file.good() << '\n';
	stringstream buffer;
	buffer << file.rdbuf();

	string ok;
	{/* Generate response */	
		/* Generate first line */
		ok = "HTTP/1.1 200 OK\n";
		
		/* Generate headers */
		ok += this->header_get_content_type(requested_file);
		ok += "Content-length: " + ft_to_string(buffer.str().length()) + '\n';
		
		/* Add body */
		ok += "\n" + buffer.str();
	}

	/* Send response */
	this->send(sockets[index].fd, ok);
}
