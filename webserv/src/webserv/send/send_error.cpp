#include <webserv.hpp>

void webserv::send_error(const int index, const int error_code) {
	string error = "HTTP/1.1 200 OK\n\n" + ft_to_string(error_code); ;
	this->send(index, error);
}
