#ifndef MESSAGE_HPP
	#define MESSAGE_HPP

#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include <config_struct.hpp>
class webserv;

enum msgState {
	loadingHeaders,
	loadingBody,
	ready,
	msgError
};

class message {
private:
	msgState state;

	int fd;

	string headers_str;
	string body_str;
	string chunk_buffer;

	size_t dechunk_chunk_size;
	bool dechunk_looking_for_chunk;

	//the first line of the message from the client
	vector<string>      startLine;
	string              actualPath;
	string              path;
	vector<string>      arguments;
	//the body of the client
	map<string, string> headers;
	string              read_buffer;
	bool                valid;
	bool                chunked;
	struct stat         stat_result;
	bool                stat_state;
	struct Config_s     config;
	size_t              headersLength;
	size_t              contentLength;
	size_t              bodyLength;

	void check();

	std::string 		Host;
	void checkGet();
	void unReferer(string string);
	
	void checkPost();
	void checkDelete();
	int checkNumber(std::string string, const char *input);
	

public:

	void init();
	void reset();
	void reset(const int fd);
	
	void unChunk();
	void unHost(string string);
	void loadHeaders();
	void loadBody();
	void tryDechunk();

	message();
	~message();

	const vector<string>      &getStartLine() const;
	const string              &getPath() const;
	const string              &getURLPath() const;
	const vector<string>      &getArguments() const;
	const map<string, string> &getHeaders() const;
	const string              &getHeadersString() const;
	const string              &getBody() const;
	const string              &getOriginal() const;
	const size_t              &getContentLength() const;

	const msgState &getState() const;
	void            setState(msgState new_state);

	const bool                &isValid() const;
	bool					  &changeValid(bool _valid);
	const bool                &isChunked() const;
	void				      doUnHost(std::string string);
	void					  checkHost(string string);

	const Config_s &getConfig() const;
	const struct stat &getStat() const;
	const bool &getStatState() const;
	void redirect(webserv &server);
};

ostream &operator<<(ostream &ostr, const message &msg);

#endif
