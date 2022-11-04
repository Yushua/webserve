#include <message.hpp>
#include <ft_lib.hpp>
#include <colors.hpp>

void message::loadBody() {
	
	char buffer[PIPE_BUF];
	int ret;
	
	ret = read(fd, buffer, PIPE_BUF);
	if (ret == -1)
		{ this->state = msgError; return; }
	if (ret == 0)
		{ this->state = ready; return; }

	this->body_str.append(buffer, ret);

	if (ret < PIPE_BUF)
		this->state = ready;
}
