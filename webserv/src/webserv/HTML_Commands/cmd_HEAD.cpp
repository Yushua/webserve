#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void webserv::cmd_HEAD(const int index, const message &msg) {

	if (!msg.getStatState()) {
		this->send_new_error(index, 404);
		return;
	}

	string requested_file;
	if (S_ISDIR(msg.getStat().st_mode)) {
		const string &dir_behavior = msg.getConfig().dir_behavior;
		if (dir_behavior == "error") {
			this->send_new_error(index, 403);
			return;
		}
		if (dir_behavior == "error") {
			this->send_new_error(index, 403);
			return;
		}
		requested_file = dir_behavior;
	}
	else
		requested_file = msg.getPath();

	if (sockets_info[index].recieving_from_server)
		close(sockets_info[index].send_fd);

	string headers = "HTTP/1.1 200 OK\n";
	struct stat file_info;
	if (stat(requested_file.c_str(), &file_info) == -1)
		ft_error("HEAD");
	headers += this->header_get_content_type(requested_file);
	headers += "Content-length: " + ft_to_string(file_info.st_size) + "\n\n";

	if (sockets_info[index].recieving_from_server)
		close(sockets_info[index].send_fd);
	else
		sockets_info[index].recieving_from_server = true;

	::send(sockets[index].fd, headers.c_str(), headers.length(), 0);

#ifdef DEBUG
	cout << MAGENTA << "  -~={ " << index << " got it's headers }=~-\n" << RESET;
	cout << headers;
#endif
}
