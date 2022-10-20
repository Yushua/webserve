#include <message.hpp>

//each msg has their own bool NOW
#include <iostream>
#include <string>
#include <ctype.h>
#include <fcntl.h>

void message::checkGet()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	for (; itr != end; ++itr){
		if (itr->first == "Host:"){
			this->unHost(itr->second);
		}
		else if (itr->first == "Referer"){
			this->unReferer(itr->second);
		}
	}
}

void message::checkPost()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();

	for (; itr != end; ++itr){
		if (itr->first == "Content-Length:" && checkNumber(itr->second, "0123456789")){
			this->contentLength = atoi(itr->second.c_str());
		}
		else if (itr->first == "Host:"){
			this->unHost(itr->second);
		}
	}
}

void message::checkDelete()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	for (; itr != end; ++itr){
		if (itr->first == "Host:"){
			this->unHost(itr->second);
		}
	}

}

void message::check()
{
	//get the
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
