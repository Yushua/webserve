#include <webserv.hpp>
#include <fstream>
#include <iostream>
#include <cstdio>

void webserv::cmd_DELETE(const int index, const message &msg) {

	/*
		DELETE /file.html HTTP/1.1
		Host: example.com
	*/

	ifstream _file;
	_file.open(msg.getPath());
	if (_file.good()) {
		int result;
		result = remove(msg.getPath().c_str());
	}
	else{
		this->send_new_error(index, 404);
	}
}
