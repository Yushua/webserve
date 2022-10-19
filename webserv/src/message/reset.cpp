#include <message.hpp>

void message::reset() {
	read_buffer.clear();
	startLine.clear();
	path.clear();
	arguments.clear();
	headers.clear();
	read_buffer.clear();
	valid = false;
	bodyComplete = false;
	headersComplete = false;
	contentLength = 0;
	headersLength = 0;
}
