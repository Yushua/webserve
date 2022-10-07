#ifndef MESSAGE_HPP
	#define MESSAGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#ifndef READ_BUFFER_SIZE
	#define READ_BUFFER_SIZE 1024
#endif

class message {
private:
	message();
	void init();

	//the first line of the message from the client
	vector<string>      startLine;
	string              path;
	vector<string>      arguments;
	//the body of the client
	map<string, string> headers;
	string              body;
	string              read_buffer;
	bool                valid;

	void check();
	void unchunk();

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
};

ostream &operator<<(ostream &ostr, const message &msg);

#endif
