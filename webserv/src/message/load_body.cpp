#include <message.hpp>
#include <ft_lib.hpp>

void message::loadBody() {
	char temp_buffer[READ_BUFFER_SIZE + 1];
	int ret;
	ret = read(fd, temp_buffer, READ_BUFFER_SIZE);
	if (ret < 0)
		ft_error("loadBody");
	if (ret == 0) {
		bodyComplete = true;
		return;
	}
	temp_buffer[ret] = '\0';
	read_buffer += temp_buffer;
	bodyLength = ret;
}
