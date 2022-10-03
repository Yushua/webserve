#include <message.hpp>

message::message(){
	this->complete = true;
	this->valid = false;
	this->chunked = false;
}
message::message(const message &other)
	{ *this = other; }
message &message::operator=(const message &other) {
	startLine   = other.startLine;
	headers     = other.headers;
	body        = other.body;
	read_buffer = other.read_buffer;
	valid = other.valid;
	complete = other.complete;
	chunked = other.chunked;
	return *this;
}
message::~message(){}

const vector<string> &message::getStartLine() const
	{ return startLine; }

const map<string, string> &message::getHeaders() const
	{ return headers; }

const string &message::getBody() const
	{ return body; }
	
const string &message::getOriginal() const
	{ return read_buffer; }

const bool &message::isValid() const
	{ return valid; }

const bool &message::isComplete() const
	{ return complete; }
const bool &message::isChunked() const
	{ return chunked; }
