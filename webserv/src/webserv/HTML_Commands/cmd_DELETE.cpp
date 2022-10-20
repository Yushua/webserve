#include <webserv.hpp>
#include <fstream>
#include <iostream>
#include <cstdio>

void webserv::cmd_DELETE(const int index, const message &msg) {
	this->send_new_error(index, 202);
	struct stat file_info;
	if (stat(msg.getPath().c_str(), &file_info) == -1)
	{
		this->send_new_error(sockets[index].fd, 404);
		this->disconnect_socket(index);
		return;
	}
	this->send_new_error(index, 204);
	ifstream _file;
	_file.open(msg.getPath());
	if (_file.good()) {
		int result;
		result = remove(msg.getPath().c_str());
		if (stat(msg.getPath().c_str(), &file_info) == -1)
		{
			this->send_new_error(sockets[index].fd, 200);
			return;
		}
	}
	else{
		this->send_new_error(index, 404);
		this->disconnect_socket(index);
			return;
	}
}
