#include <message.hpp>

//each msg has their own bool NOW
#include <iostream>
#include <string>
#include <ctype.h>

void message::check()
{
	// vector<string>::iterator itr_v = startLine.begin();
	// vector<string>::iterator end_v = startLine.end();
	// for (; itr_v < end_v; itr_v++)
	// {
	// 	std::cout << *itr_v << " " << std::endl;
	// }
	
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	// std::vector<std::string> store;//dont' forget to delete it
	std::string Host;
	//why three times?
	for (; itr != end; ++itr)
	{
		if (itr->first == "Transfer-Encoding:")
		{
			this->unchunk();
		}
		else if (itr->first == "Host:")
		{
			if (this->unHost(itr->second))
				Host = itr->second;
			else
				valid = false;
		}
		else if (itr->first == "Referer:")
		{
			if (this->unReferer(itr->second, Host))
				valid = true;
			else
				valid = false;
		}
		std::cout << itr->first << " " << itr->second << std::endl;
	}
	// std::cout << " " << std::endl;

	// if error == 400
	// 	valid = false;
	valid = true;
}

void message::unchunk()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();

	for (; itr != end; ++itr)
	{
		if (itr->first == "Transfer-Encoding:")
			break;
	}
	std::cout << "hello i am here\n\n";
}

static int checkNumber(std::string string)
{
	return string.find_first_not_of("0123456789") == string::npos;
}

bool message::unHost(string string)
{
	//127.0.0.1:4243
	int ip = 4;
	int i = 0;
	std::string tmp = string.substr(0, string.find(":"));
	// std::string check = "";
	while(ip != 0){
		i = tmp.find(".");
		if(i == 0 && checkNumber(tmp) != -1)
		{
			// std::cout << check << std::endl;
			break;
		}
		if(i == 0 && checkNumber(tmp) == -1)
			return false;
		// check = tmp.substr(0, i);
		if(checkNumber(tmp.substr(0, i)) == -1)
			return false;
		tmp.erase(0, i+1);
		// std::cout << check << std::endl;
		ip--;
	} 
	// check = string.substr(string.find(":") + 1, string.length());
	// std::cout << "port ==: " <<  check << std::endl;
	if(checkNumber(string.substr(string.find(":") + 1, string.length())) == -1)
		return false;
	return true;
}

bool message::unReferer(string string, std::string host)
{
	//http://127.0.0.1:4243/page2.html
	//make it smaller by directly putting everything in
	std::string check;
	std::cout << "string ==" << host << std::endl;
	if(string.substr(0, 7) != "http://")
		return false;
	if (string.substr(7, host.length() - 1) == host)
		return false;
	check = string.substr(host.length() + 6,  string.length());
	// std::cout << "check == " << check << std::endl;
	if (check == "/")
		return true;
	//check path
	string = " ";
	host = " ";
	return true;
}

/*

General Header

Request Header

Response Header

Entity Header


GET PUT DELETE POST HEAD


*/
