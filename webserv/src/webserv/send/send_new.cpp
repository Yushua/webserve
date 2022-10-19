#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

void webserv::send_new(const int index, string headers, const int fd) {

	::send(sockets[index].fd, headers.c_str(), headers.length(), 0);

	if (sockets_info[index].recieving_from_server)
		close(sockets_info[index].send_fd);
	else
		sockets_info[index].recieving_from_server = true;
	
	sockets_info[index].send_fd = fd;
	sockets_info[index].disconnect_after_send = false;

#ifdef DEBUG
	cout << MAGENTA << "  -~={ " << index << " is recivign this }=~-\n" << RESET;
	cout << headers;
#endif
}
