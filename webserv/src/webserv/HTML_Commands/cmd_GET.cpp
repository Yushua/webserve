#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void webserv::cmd_GET(const int index, const message &msg) {

	if (msg.getStatResult() == -1)
		this->send_error(index, 404);

	string requested_file;
	if (S_ISDIR(msg.getStatResult())) {
		const string &dir_behavior = msg.getConfig().dir_behavior;
		if (dir_behavior == "list") {
			this->send_error(index, 403); /* !!!IMPLEMENT INDEXING!!! */
			return;
		}
		else if (dir_behavior == "error") {
			this->send_error(index, 403);
			return;
		}
		requested_file = dir_behavior;
	}
	else
		requested_file = msg.getPath();

	/* Open file in root */
	ifstream file(requested_file);

	/* Check if path exists */
	if (!file.good()) {
		this->send_error(index, 404);
		return;
	}

	/* Read file */
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	/* Checking if it's a cgi request */
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
