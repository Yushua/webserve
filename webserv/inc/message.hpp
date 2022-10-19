#ifndef MESSAGE_HPP
	#define MESSAGE_HPP

#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include <config_struct.hpp>
class webserv;

#ifndef READ_BUFFER_SIZE
	#define READ_BUFFER_SIZE 1024
#endif

class message {
private:
	bool headersComplete;
	bool bodyComplete;

	int fd;

	//the first line of the message from the client
	vector<string>      startLine;
	string              path;
	vector<string>      arguments;
	//the body of the client
	map<string, string> headers;
	string              read_buffer;
	bool                valid;
	bool				chunkS;
	bool				chunkE;
	struct stat         stat_result;
	bool                stat_state;
	struct Config_s     config;
	size_t              headersLength;
	size_t              contentLength;
	size_t              bodyLength;

	void check();
	void unChunk();

	std::string 		Host;
	void checkGet();
	void unHost(string string);
	void unReferer(string string);
	
	void checkPost();
	void checkDelete();
	int checkNumber(std::string string, const char *input);
	
	void reset();

public:
	void init(const int fd);
	void loadBody();

	message();
	~message();

	const vector<string>      &getStartLine() const;
	const string              &getPath() const;
	const vector<string>      &getArguments() const;
	const map<string, string> &getHeaders() const;
	const char                *getBody() const;
	const string              &getOriginal() const;
	const size_t              &getContentLength() const;
	const size_t              &getBodyLength() const;

	const bool &isHeaderComplete() const;
	const bool &isBodyComplete() const;

	const bool                &isValid() const;
	const bool                &isChunked() const;

	const Config_s &getConfig() const;
	const struct stat &getStat() const;
	const bool &getStatState() const;
	void redirect(webserv &server);
};

ostream &operator<<(ostream &ostr, const message &msg);

#endif
