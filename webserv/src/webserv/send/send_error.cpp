#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void webserv::send_new_error(const int index, const int error_code) {

	string headers = "HTTP/1.1 " + ft_to_string(error_code) + '\n';
	string &error_page = error_pages.at(error_code);

	headers += this->header_get_content_type(error_page);

	this->send_new_file(index, headers, error_page);
}
