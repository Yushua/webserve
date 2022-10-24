#include <message.hpp>
#include <ft_lib.hpp>
#include <colors.hpp>

#undef PIPE_BUF
#define PIPE_BUF 20

void message::loadHeaders() {
	
	this->state = loadingHeaders;

	char buffer[PIPE_BUF + 1];
	int ret;

	ret = read(fd, buffer, PIPE_BUF);
	if (ret < 0)
		ft_error("loadHeaders");
	if (ret == 0)
		{ this->state = loadingBody; return; }
	buffer[ret] = '\0';

	size_t index = this->headers_str.length();
	if (index != 0)
		index -= 3;
	this->headers_str += buffer;
	size_t end = this->headers_str.length();

	bool double_nl = false;
	for (; index < end; ++index) {
		if (headers_str[index] == '\n') {
			if (double_nl)
				break;
			double_nl = true;
		}
		else if (!(double_nl && headers_str[index] == '\r'))
			double_nl = false;
	}

	if (index != end) {
		++index;
		this->body_str += headers_str.substr(index, end - index);
		this->headers_str.erase(index, end - index);
		this->state = loadingBody;
		return;
	}
	
	if (ret < PIPE_BUF)
		this->state = loadingBody;
}
