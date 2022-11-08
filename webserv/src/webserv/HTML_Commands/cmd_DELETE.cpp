#include <webserv.hpp>
#include <fstream>
#include <iostream>
#include <cstdio>

void webserv::cmd_DELETE(const int index, const message &msg) {
	this->send_new_error(index, 202);
	ofstream file;
	struct stat file_info;
	if (msg.getStatState())
	{
		/* if it is a folder*/
		if (S_ISDIR(msg.getStat().st_mode)){
			this->send_new_error_fatal(index, 403);
			return;
		}
		/* if it is a file*/
		ifstream _file;
		_file.open(msg.getPath());
		if (_file.good()) {
			int result;
			result = remove(msg.getPath().c_str());
			if (stat(msg.getPath().c_str(), &file_info) == -1)
			{
				this->send_new_error(index, 204);
				return;
			}
		}
		else{
			this->send_new_error_fatal(index, 404);
				return;
		}
	}
	else{//if it does not exist
		this->send_new_error_fatal(index, 404);
		return;
	}
}

/*
curl 127.0.0.1:4242/cgi-bin/lol.lol -X DELETE -v

*/
