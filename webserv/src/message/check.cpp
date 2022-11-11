#include <message.hpp>
#include <string>
#include <iostream>

void message::checkPost()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();

	for (; itr != end; ++itr) {
		if (itr->first == "Content-Length:" && checkNumber(itr->second, "0123456789"))
			{ this->contentLength = atoi(itr->second.c_str());
		}
	}
}

void message::check()
{
	vector<std::string>::iterator itr_v = startLine.begin();
	vector<std::string>::iterator end_v = startLine.end();
	for (; itr_v < end_v; itr_v++)
	{
		if (*itr_v == "POST")
			checkPost();
	}
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	for (; itr != end; ++itr)
	{
		std::string string = itr->first;
		if (string.at(string.length()-1) != ':')
			{ return; }
		string.pop_back();
		if (string.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") != string::npos)
			{ return; }
	}
	this->valid = true;
}
