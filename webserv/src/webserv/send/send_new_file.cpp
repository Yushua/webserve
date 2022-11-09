#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <algorithm>

void webserv::send_new_file(const int index, string headers, const string path) {

	int fd;
	struct stat file_info;
	
	{/* Check if file exists and open it */
		if (stat(path.c_str(), &file_info) == -1)
			ft_error("send_new_file");

		fd = open(path.c_str(), O_RDONLY);
		if (fd < 0)
			ft_error("send_new_file");
	}

	/* Generate headers */
	headers += this->header_get_content_type(path);
	headers += "Content-Length: " + ft_to_string(file_info.st_size) + "\n\n";

	this->send_new(index, headers, fd);
}
