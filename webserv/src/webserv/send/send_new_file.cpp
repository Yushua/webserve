#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

void webserv::send_new_file(const int index, string headers, const string path) {

	if (sockets_info[index].recieving_from_server)
		close(sockets_info[index].send_fd);
	int fd = open(path.c_str(), O_RDONLY);
	if (fd < 0)
		ft_error("send_new_file");

	struct stat file_info;
	if (stat(path.c_str(), &file_info) == -1)
		ft_error("send_new_file");
	headers += this->header_get_content_type(path);
	headers += "Content-length: " + ft_to_string(file_info.st_size) + "\n\n";

	this->send_new(index, headers, fd);
}