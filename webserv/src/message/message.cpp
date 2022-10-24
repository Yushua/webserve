#include <message.hpp>

message::message() {
	this->state = loadingHeaders;
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

const string &message::getHeadersString() const
	{ return headers_str; }
const string &message::getBody() const
	{ return body_str; }
	
const string &message::getOriginal() const
	{ return read_buffer; }

const bool &message::isValid() const
	{ return valid; }

bool &message::changeValid(bool _valid)
	{ return (valid = _valid); }

const Config_s &message::getConfig() const
	{ return config; }

const struct stat &message::getStat() const
	{ return stat_result; }

const bool &message::getStatState() const
	{ return stat_state; }

const size_t &message::getContentLength() const
	{ return contentLength; }

void message::doUnHost(std::string string)
	{ unHost(string); return ;}

const msgState &message::getState() const
	{ return state; }

void message::setState(msgState new_state)
	{ this->state = new_state; }
