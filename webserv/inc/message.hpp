#ifndef MESSAGE_HPP
	#define MESSAGE_HPP

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
	message();
	void init();

	bool isFileDirec;

	//the first line of the message from the client
	vector<string>      startLine;
	string              path;
	vector<string>      arguments;
	//the body of the client
	map<string, string> headers;
	string              body;
	string              read_buffer;
	bool                valid;
	bool				chunkS;
	bool				chunkE;
	int                 stat_result;
	struct Config_s     config;

	void check();
	void unChunk();

	std::string 		Host;
	void checkGet();
	void unHost(string string);
	void unReferer(string string);
	
	void checkPost();
	double				contLenght;
	void checkDelete();
	int checkNumber(std::string string, const char *input);

public:
	message(const int fd);
	message(const string &msg);
	message(const message &other);
	message &operator=(const message &other);
	~message();

	const vector<string>      &getStartLine() const;
	const string              &getPath() const;
	const vector<string>      &getArguments() const;
	const map<string, string> &getHeaders() const;
	const string              &getBody() const;
	const string              &getOriginal() const;

	const bool                &isValid() const;
	const bool                &isComplete() const;
	const bool                &isChunked() const;
	void				  setContLenght(double _contLenght);

	const Config_s &getConfig() const;
	const int &getStatResult() const;
	void redirect(webserv &server);
};

ostream &operator<<(ostream &ostr, const message &msg);

#endif
