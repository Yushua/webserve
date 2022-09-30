#include <webserv.hpp>

void webserv::send_error(const int fd, const int error_code) {
	string error = "HTTP/1.1 200 OK\n\n" + ft_to_string(error_code); ;
	this->send(fd, error);
}
