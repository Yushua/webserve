#include <message.hpp>

message::message() {
	headersComplete = true;
	bodyComplete = true;
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

const char *message::getBody() const
	{ return read_buffer.c_str() + headersLength; }
	
const string &message::getOriginal() const
	{ return read_buffer; }

const bool &message::isValid() const
	{ return valid; }

const Config_s &message::getConfig() const
	{ return config; }

const struct stat &message::getStat() const
	{ return stat_result; }

const bool &message::getStatState() const
	{ return stat_state; }

const bool &message::isHeaderComplete() const
	{ return headersComplete; }

const bool &message::isBodyComplete() const
	{ return bodyComplete; }

const size_t &message::getContentLength() const
	{ return contentLength; }

const size_t &message::getBodyLength() const
	{ return bodyLength; }
