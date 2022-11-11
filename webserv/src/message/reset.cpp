#include <message.hpp>
#include <colors.hpp>

void message::reset() {
	this->startLine.clear();
	this->path.clear();
	this->arguments.clear();
	this->headers.clear();
	this->valid = false;
	this->state = loadingHeaders;
	this->contentLength = 0;
	this->body_str.clear();
	this->headers_str.clear();
	this->chunk_buffer.clear();

	this->amount_read = 0;
	this->chunked = false;
	this->dechunk_looking_for_chunk = true;
	this->dechunk_chunk_size = 0;
}

void message::reset(const int new_fd) {
	this->fd = new_fd;
	this->reset();
}
