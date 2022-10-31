#include <message.hpp>
#include <ft_lib.hpp>
#include <colors.hpp>

void message::loadBody() {
	
	char buffer[PIPE_BUF + 1];
	int ret;
	
	ret = read(fd, buffer, PIPE_BUF);
	if (ret == -1)
		{ this->state = msgError; return; }
	if (ret == 0)
		{ this->state = ready; return; }
	buffer[ret] = '\0';

	this->body_str += buffer;

	if (ret < PIPE_BUF)
		this->state = ready;
}
