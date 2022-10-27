#include <message.hpp>
#include <ft_lib.hpp>
#include <colors.hpp>

void message::loadBody() {
	
	char buffer[PIPE_BUF + 1];
	int ret;
	
	ret = recv(fd, buffer, PIPE_BUF, 0);
	if (ret < 0)
		ft_error("loadBody");
	if (ret == 0) {
		this->state = ready;
		return;
	}
	buffer[ret] = '\0';

	this->body_str += buffer;

	cerr << buffer;

	if (ret < PIPE_BUF)
		this->state = ready;
}
