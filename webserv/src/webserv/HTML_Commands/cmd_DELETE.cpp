#include <webserv.hpp>
#include <fstream>
#include <iostream>
#include <cstdio>  

void webserv::cmd_DELETE(const int index, const message &msg) {
	fstream file;
	if (!msg.getStatState())
		{ this->send_new_error(index, 404); return; }

	/* permission denied */
	if (!S_ISREG(msg.getStat().st_mode)) {
		this->send_new_error_fatal(index, 403);
		return;
	}

	/* if failed */
	int result;
	result = remove(msg.getPath().c_str());
	std::cout << result << std::endl;
	if (result != -1)
	{
		this->send_new(index, "HTTP/1.1 204\nContent-Length: 0\n\n", -1);
		return;
	}
	this->send_new_error_fatal(index, 500);
}
