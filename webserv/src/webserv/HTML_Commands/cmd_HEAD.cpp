#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void webserv::cmd_HEAD(const int index, const message &msg) {

	/* ??????? Maybe see if you don't have to read the file ??????? */

	string requested_file = msg.getPath();
	if (requested_file == "/")
		 requested_file = "/index.html";
	requested_file = "root" + requested_file;

	/* Open file in root */
	ifstream file(requested_file);

	/* Check if path exists */
	if (!file.good()) {
		this->send_error(index, 404);
		//this->disconnect_socket(index);
		return;
	}

	/* Read file */
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	string ok;
	{/* Generate response */	
		/* Generate first line */
		ok = "HTTP/1.1 200 OK\n";
		
		/* Generate headers */
		ok += this->header_get_content_type(requested_file);
		ok += "Content-length: " + ft_to_string(buffer.str().length()) + '\n';
	}

	/* Send response */
	this->send(index, ok);
}
