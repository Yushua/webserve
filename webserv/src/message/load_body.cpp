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

	if (chunked)
		this->chunk_buffer.append(buffer, ret);
	else
		this->body_str.append(buffer, ret);
}
