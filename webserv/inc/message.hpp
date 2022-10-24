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
	
	/**
	 * @brief unchunk checks if the chunk is correct, changes the VALID Bool in Message
	 * 
	 */
	void unChunk();
	/**
	 * @brief unhost checks if the Host is valid, changes the VALID bool in Message
	 * 
	 */
	void unHost(string string);

	void loadBody();
	void loadHeaders();

	message();
	~message();

	const vector<string>      &getStartLine() const;
	const string              &getPath() const;
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

	const Config_s &getConfig() const;
	const struct stat &getStat() const;
	const bool &getStatState() const;
	void redirect(webserv &server);
};

ostream &operator<<(ostream &ostr, const message &msg);

#endif
