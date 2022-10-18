#include <message.hpp>
#include <ft_lib.hpp>
#include <unistd.h>
#include <iostream>

void message::init(const int fd) {
	this->fd = fd;
	this->reset();

	/* !!! NEEDS BE REIMPLEMENTED !!! */
	/* It's slow and error prone */
	bool double_nl = false;
	while (true) {
		char temp_buffer;
		int ret;
		ret = read(fd, &temp_buffer, 1);
		if (ret <= 0)
			break;
		read_buffer += temp_buffer;
		if (temp_buffer == '\n' && double_nl) {
			if (double_nl)
				break;
			double_nl = false;
		}
		else {
			double_nl = false;
		}
	}

	size_t len = read_buffer.length();
	if (len == 0)
		return;
	size_t index;

	{/* Get StartLine */
		int start = 0;
		for (index = 0; index < len; ++index) {
			if (read_buffer[index] == ' ') {
				startLine.push_back(read_buffer.substr(start, index - start));
				start = ++index;
			}
			else if (read_buffer[index] == '\n') {
				startLine.push_back(read_buffer.substr(start, index - start));
				break;
			}
		}
	}

	if (startLine.size() < 2)
		return;

	{/* Get path and arguments */
		string &url = startLine.at(1);
		size_t len = url.length();
		size_t index = 0;
		bool hadArgs = false;
		for (; index < len; ++index) {
			if (url[index] == '?') {
				hadArgs = true;
				break;
			}
		}
		path = url.substr(0, index);
		if (hadArgs) {/* Get Headers */
			int start = ++index;
			string name, value;
			for (; index < len; ++index) {
				if (url[index] == '&') {
					arguments.push_back(url.substr(start, index - start));
					start = ++index;
				}
			}
			arguments.push_back(url.substr(start, index - start));
		}
	}

	{/* Get Headers */
		bool gettingHeader = true;
		int start = ++index;
		string head, value;
		for (; index < len; ++index) {
			if (gettingHeader && read_buffer[index] == ' ') {
				gettingHeader = false;
				head = read_buffer.substr(start, index - start);
				start = ++index;
			}
			else if (read_buffer[index] == '\n') {
				if (!gettingHeader) {
					gettingHeader = true;
					value = read_buffer.substr(start, index - start);
					headers.insert(pair<string, string>(head, value));
					start = ++index;
				}
				else
					break;
			}
		}
	}

	/* Check Message Validity */
	this->check();

	headersComplete = true;
	if (contentLenght == 0)
		bodyComplete = true;
}
