#include <message.hpp>
#include <ft_lib.hpp>
#include <unistd.h>
#include <iostream>

message::message(const int fd) {
	read_buffer = ft_fd_to_str(fd);
	this->init();
}

message::message(const string &msg) {
	read_buffer = msg;
	this->init();
}

void message::init() {
	size_t len = read_buffer.length();
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

	/* Get Body */
	body = read_buffer.substr(index, read_buffer.length() - index);

	/* Check Message Validity */
	this->check();
}
