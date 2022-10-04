#include <webserv.hpp>

const string ft_fd_to_str(const int fd) {
	string read_buffer;
	while (true) {
		char temp_buffer[READ_BUFFER_SIZE + 1];
		int ret;
		ret = read(fd, temp_buffer, READ_BUFFER_SIZE);
		if (ret <= 0)
			break;
		temp_buffer[ret] = '\0';
		read_buffer += temp_buffer;
	}
	return read_buffer;
}
