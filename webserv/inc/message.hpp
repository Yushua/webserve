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
	//the body of the client
	map<string, string> headers;
	string              body;
	string				read_buffer;
	bool                valid;
	bool				complete;
	bool				chunked;

	void check(); /* !!!TO BE IMPLEMENETD!!! */
	void unchunk(); /* !!!TO BE IMPLEMENETD!!! */
	bool unHost(string string); /* !!!TO BE IMPLEMENETD!!! */
	bool unReferer(string string, std::string host); /* !!!TO BE IMPLEMENETD!!! */

public:
	message(const int fd);
	message(const string &msg);
	message(const message &other);
	message &operator=(const message &other);
	~message();

	const vector<string>      &getStartLine() const;
	const map<string, string> &getHeaders() const;
	const string              &getBody() const;
	const string              &getOriginal() const;

	const bool                &isValid() const;
	const bool                &isComplete() const;
	const bool                &isChunked() const;
};

ostream &operator<<(ostream &ostr, const message &msg);

#endif
