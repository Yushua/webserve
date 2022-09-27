#include <message.hpp>
#include <unistd.h>
#include <iostream>

message::message(const int fd) {
	while (true) {
		char temp_buffer[READ_BUFFER_SIZE + 1];
		int ret;
		ret = read(fd, temp_buffer, READ_BUFFER_SIZE);
		if (ret <= 0)
			break;
		temp_buffer[ret] = '\0';
		read_buffer += temp_buffer;
	}
	this->init();
}

message::message(const string &msg) {
	read_buffer = msg;
	this->init();
}

void message::init() {
	int index;
	{/* Get StartLine */
		int start = 0;
		for (index = 0; read_buffer[index]; ++index) {
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
		for (; read_buffer[index]; ++index) {
			if (gettingHeader && read_buffer[index] == ' ') {
				gettingHeader = false;
				head = read_buffer.substr(start, index - start - 1);
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
}
