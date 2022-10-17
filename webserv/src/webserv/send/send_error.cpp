#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void webserv::send_new_error(const int index, const int error_code) {

	string headers = "HTTP/1.1 200 OK\n";
	
	headers += this->header_get_content_type(".html");

	this->send_new_file(index, headers, error_pages.at(error_code));
}
