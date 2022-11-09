#include <message.hpp>
#include <ft_lib.hpp>
#include <colors.hpp>

void message::loadHeaders() {

	this->state = loadingHeaders;

	char buffer[PIPE_BUF];
	int ret;

	ret = read(fd, buffer, PIPE_BUF);
	if (ret == -1)
		{ this->state = msgError; return; }
	if (ret == 0)
		{ this->state = loadingBody; return; }

	size_t index = this->headers_str.length();
	if (index != 0)
		--index;
	this->headers_str.append(buffer, ret);
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
}
