#ifndef MESSAGE_HPP
	#define MESSAGE_HPP

#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
#include <fcntl.h>
#include <fstream>

#include <colors.hpp>

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

	int             fd;
	msgState        state;
	struct Config_s config;
	bool            valid;
	bool            chunked;

	/* Dechunk */
		size_t  dechunk_chunk_size;
		bool    dechunk_looking_for_chunk;

	/* Start Line */
		vector<string> startLine;
		string         path;
		string         actualPath;
		vector<string> arguments;
		struct stat    stat_result;
		bool           stat_state;

	/* Headers */
		map<string, string> headers;
		string              headers_str;

	/* Body */
		size_t  contentLength;
		string  body_str;
		string  chunk_buffer;


	void check();

public:

	message();
	~message();

	void init();
	void reset();
	void reset(const int fd);
	
	void loadHeaders();
	void loadBody();

	void tryDechunk();
	
	void redirect(webserv &server);

	const vector<string>      &getStartLine() const;
	const string              &getPath() const;
	const string              &getURLPath() const;
	const vector<string>      &getArguments() const;
	const map<string, string> &getHeaders() const;
	const string              &getHeadersString() const;
	const string              &getBody() const;
	const size_t              &getContentLength() const;
	const msgState            &getState() const;
	const Config_s            &getConfig() const;
	const struct stat         &getStat() const;
	const bool                &getStatState() const;
	
	void                      setState(msgState new_state);

	const bool                &isValid() const;
	const bool                &isChunked() const;
};

#endif
