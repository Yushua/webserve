#include <message.hpp>
#include <string>
#include <iostream>

void message::check()
{
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
