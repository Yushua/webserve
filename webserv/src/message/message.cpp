#include <message.hpp>

message::message(){
	this->valid = false;
	this->contLenght = 0;
}
message::message(const message &other)
	{ *this = other; }
message &message::operator=(const message &other) {
	startLine   = other.startLine;
	headers     = other.headers;
	body        = other.body;
	read_buffer = other.read_buffer;
	valid = other.valid;
	contLenght = other.contLenght;
	return *this;
}
message::~message(){}

const vector<string> &message::getStartLine() const
	{ return startLine; }

const string &message::getPath() const
	{ return path; }
const vector<string> &message::getArguments() const
	{ return arguments; }

const map<string, string> &message::getHeaders() const
	{ return headers; }

const string &message::getBody() const
	{ return body; }
	
const string &message::getOriginal() const
	{ return read_buffer; }

const int &message::getContLenght() const
	{ return contLenght; }

const bool &message::isValid() const
	{ return valid; }

// const bool &message::isChunked() const
// 	{ return chunked; }
