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
		if (itr->first == "Content-Length:" && checkNumber(itr->second, "0123456789")){
			setContLenght(atoi(itr->second.c_str()));
			if (this->contLenght != getBody().length())
				this->valid = false;
			else
				this->valid = true;
		}
		else if (itr->first == "Host:"){
			this->unHost(itr->second);
		}
		else if ((itr->first == "Transfer-Encoding:" || itr->first == "TE:" ) && itr->second.find("chunked")){
			this->unChunk(itr->second);
			//wjile still waiitng for other chunks
			//hving recieved last chunk
			// if (chunkE == true && chunkS == true)
			// 	this->valid = true;
			// else if (chunkS == true && chunkE == false)
			// 	this->valid = false;
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
		if (*itr_v == "GET" || *itr_v == "HEAD")
			checkGet();
		else if (*itr_v == "POST")
			checkPost();
		else if (*itr_v == "DELETE")
			checkDelete();
	}
}
