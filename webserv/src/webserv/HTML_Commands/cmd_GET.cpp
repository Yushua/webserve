#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void webserv::cmd_GET(const int index, const message &msg) {

	/* ??????? Maybe try differentiating between files and dirs ??????? */

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

	/* Checking if it's a python script */
	string extension = ft_get_extension(requested_file);
	map<string, string>::iterator key = cgi_options.find(extension);
	if (key != cgi_options.end()) {
		cgi_get(index, msg, requested_file, key->second);
		return;
	}

	string ok;
	{/* Generate response */	
		/* Generate first line */
		ok = "HTTP/1.1 200 OK\n";
		
		/* Generate headers */
		ok += this->header_get_content_type(extension);
		ok += "Content-length: " + ft_to_string(buffer.str().length()) + '\n';
		
		/* Add body */
		ok += "\n" + buffer.str();
	}

	/* Send response */
	this->send(index, ok);
}
