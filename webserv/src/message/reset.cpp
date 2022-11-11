#include <message.hpp>
#include <colors.hpp>

void message::reset() {
	this->read_buffer.clear();
	this->startLine.clear();
	this->path.clear();
	this->arguments.clear();
	this->headers.clear();
	this->read_buffer.clear();
	this->valid = false;
	this->state = loadingHeaders;
	this->contentLength = 0;
	this->headersLength = 0;
	this->body_str.clear();
	this->headers_str.clear();
	this->chunk_buffer.clear();

	this->chunked = false;
	this->dechunk_looking_for_chunk = true;
	this->dechunk_chunk_size = 0;
}

void message::reset(const int new_fd) {
	this->fd = new_fd;
	this->reset();
}
