#include <message.hpp>

#include <iostream>
#include <string>
#include <ctype.h>
#include <fcntl.h>
#include <fstream>

void message::unHost(string string)
{
	int ip = 0;
	int i = 0;
	//check for defaulthost
	while (string.find(".") != string::npos)
	{
		i = string.find(".");
		if(checkNumber(string, "0123456789") != -1) {
			// std::cout << check << std::endl;
			this->valid = false;
		}
		string.erase(0, i+1);
		ip++;
	}
	if (string.find(":") != string::npos) {
		i = string.find(":");
		if(checkNumber(string, "0123456789") != -1) {
			// std::cout << check << std::endl;
			this->valid = false;
		}
		ip++;
	}
	if (ip != 4)
		this->valid = false;
    this->Host = string;
	this->valid = true;
}

void message::unReferer(string string)
{
	if (string.substr(0, 7) != "http://")
		this->valid = false;
	if (string.substr(7, this->Host.length() - 1) == this->Host)
		this->valid = false;
	std::string check = string.substr(this->Host.length() + 6,  string.length());
	if (check == "/")
		this->valid = true;
	
	ifstream _file;
	_file.open(check);
	if (!_file.good()) {
		this->valid = false;
	}
	this->valid = true;
}

void message::checkGet()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	for (; itr != end; ++itr) {
		if (itr->first == "Host:") {
			this->unHost(itr->second);
		}
		else if (itr->first == "Referer") {
			this->unReferer(itr->second);
		}
	}
}

void message::checkPost()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();

	for (; itr != end; ++itr) {
		if (itr->first == "Content-Length:" && checkNumber(itr->second, "0123456789")) {
			this->contentLength = atoi(itr->second.c_str());
		}
		else if (itr->first == "Host:") {
			this->unHost(itr->second);
		}
	}
}

void message::checkDelete()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	for (; itr != end; ++itr) {
		if (itr->first == "Host:") {
			this->unHost(itr->second);
		}
	}

}

void message::check()
{
	vector<std::string>::iterator itr_v = startLine.begin();
	vector<std::string>::iterator end_v = startLine.end();
	for (; itr_v < end_v; itr_v++)
	{
		if (*itr_v == "GET")
			checkGet();
		else if (*itr_v == "POST")
			checkPost();
		else if (*itr_v == "DELETE")
			checkDelete();
	}
}
