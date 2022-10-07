#include <message.hpp>

//each msg has their own bool NOW
#include <iostream>
#include <string>
#include <ctype.h>
#include <fcntl.h>

void message::getCheck()
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

void message::postCheck()
{
	/*
	POST /echo/post/json HTTP/1.1
	Authorization: Bearer mt0dgHmLJMVQhvjpNXDyA83vA_Pxh33Y
	Accept: application/json
	Content-Type: application/json
	Content-Length: 85
	Host: reqbin.com

	{
		"Id": 12345,
		"Customer": "John Smith",
		"Quantity": 1,
		"Price": 10.00
	}

	do i need to check if /echo/post/json is also valid?
	*/

	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();

	string _body = body;
	for (; itr != end; ++itr){
		if (itr->first == "Content-Length:"){
			this->valid = true;
		}
		else if (itr->first == "Host:"){
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
			getCheck();
		else if (*itr_v == "POST")
			postCheck();
	}
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	std::string Host;
	for (; itr != end; ++itr){	
		std::cout << itr->first << " " << itr->second << std::endl;
	}
}
