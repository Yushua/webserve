#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void webserv::send_error(const int index, const int error_code) {

	/* Open file in root */
	ifstream file(error_pages.at(error_code));

	/* Check if path exists */
	if (!file.good()) {
		this->send_error(index, 404);
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
		ok += this->header_get_content_type(".html");
		ok += "Content-length: " + ft_to_string(buffer.str().length()) + '\n';
		
		/* Add body */
		ok += "\n" + buffer.str();
	}

	/* Send response */
	this->send(index, ok);
}
