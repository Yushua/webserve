#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

void webserv::send_new(const int index, const int fd) {

	sockets_info[index].recieving_from_server = true;
	sockets_info[index].send_fd = fd;

}
