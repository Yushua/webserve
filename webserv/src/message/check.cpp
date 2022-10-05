#include <message.hpp>

//each msg has their own bool NOW
#include <iostream>
#include <string>
#include <ctype.h>
#include <fcntl.h>

// static int checkNumber(std::string string, const char *input)
// {
// 	return string.find_first_not_of(input) == string::npos;
// }

void message::check()
{
	// // vector<string>::iterator itr_v = startLine.begin();
	// // vector<string>::iterator end_v = startLine.end();
	// // for (; itr_v < end_v; itr_v++)
	// // {
	// // 	std::cout << *itr_v << " " << std::endl;
	// // }
	
	// map<string, string>::iterator itr = headers.begin();
	// map<string, string>::iterator end = headers.end();
	// // std::vector<std::string> store;//dont' forget to delete it
	// std::string Host;
	// //why three times?
	// bool _end = false;
	// for (; itr != end; ++itr){	
	// 	if ((itr->first == "Transfer-Encoding:" || itr->first == "TE:" ) && itr->second.find("chunked"))
	// 		chunked = true;
	// 	else if (itr->first == "Host:"){
	// 		if (this->unHost(itr->second))
	// 			Host = itr->second;
	// 		else
	// 			valid = false;
	// 	}
	// 	else if (itr->first == "Referer:"){
	// 		if (this->unReferer(itr->second, Host))
	// 			valid = true;
	// 		else
	// 			valid = false;
	// 	}
	// 	else if (checkNumber(itr->first, "x0123456789ABCDEF\r\n") || checkNumber(itr->second, "x0123456789ABCDEF\r\n")){
	// 		_end = true;
	// 		break;
	// 	}
	// 	// std::cout << itr->first << " " << itr->second << std::endl;
	// }
	// if (chunked != true && _end == true)
	// 	std::cout << "chunked was announced but not used" << std::endl;
	// if (chunked == true && _end == true)
	// 	this->unchunk();
	// // std::cout << " " << std::endl;

	// // if error == 400
	// // 	valid = false;
	// valid = true;
}

// void message::unchunk()
// {
// 	map<string, string>::iterator itr = headers.begin();
// 	map<string, string>::iterator end = headers.end();
// 	bool chunkedStatus = false;
// 	bool status = false;
// 	std::string _chunk = "";
// 	for (; itr != end; ++itr)
// 	{
// 		if (checkNumber(itr->first, "x0123456789ABCDEF\r\n")){
// 			status = true;
// 			break;
// 		}
// 	}
// 	if (status == false)
// 		std::cout << "there is chunk start, but in the body" << std::endl;
// 	else{
// 		long int _size = 0;
// 		for (; itr != end; ++itr){
// 			if (checkNumber(itr->first, "0x\r\n123456789ABCDEF") == -1 || checkNumber(itr->first, "0\r\n123456789ABCDEF") == -1){
// 				status = false;
// 			}
// 			else if (itr->first.size() <= 2){
// 				std::cout << "input is too small" << std::endl;
// 				break;
// 			}
// 			else if (status == false)
// 				std::cout << "input after end of file" << std::endl;
// 			else if (chunkedStatus == false){
// 				if (checkNumber(itr->first, "0123456789ABCDEFx\r\n") == -1)
// 					std::cout << "bits is not a number" << std::endl;
// 				else if (itr->first.substr(0, 2) == "0x")
// 					std::cout << "its a hexacode" << std::endl;
// 				else if (checkNumber(itr->first, "0123456789\r\n")){
// 					std::cout << "normal" << std::endl;
// 				}
// 				else
// 					std::cout << "number not suitable" << std::endl;
// 			}
// 			else if (chunkedStatus == true){
// 				if (_size == 0)
// 					std::cout << "construct of chunk is wrong. letters before size" << std::endl;
// 				std::string tmp = itr->first;
// 				tmp.erase(tmp.size() - 2);
// 				//append the string here
// 			}
// 		}

// 	}
// 	// if (!checkNumber(itr->first, "0x0\r\n") || !checkNumber(itr->first, "0\r\n"))
// }

// bool message::unHost(string string)
// {
// 	//127.0.0.1:4243
// 	int ip = 4;
// 	int i = 0;
// 	std::string tmp = string.substr(0, string.find(":"));
// 	// std::string check = "";
// 	while(ip != 0){
// 		i = tmp.find(".");
// 		if(i == 0 && checkNumber(tmp, "0123456789") != -1)
// 		{
// 			// std::cout << check << std::endl;
// 			break;
// 		}
// 		if(i == 0 && checkNumber(tmp, "0123456789") == -1)
// 			return false;
// 		// check = tmp.substr(0, i);
// 		if(checkNumber(tmp.substr(0, i), "0123456789") == -1)
// 			return false;
// 		tmp.erase(0, i+1);
// 		// std::cout << check << std::endl;
// 		ip--;
// 	} 
// 	// check = string.substr(string.find(":") + 1, string.length());
// 	// std::cout << "port ==: " <<  check << std::endl;
// 	if(checkNumber(string.substr(string.find(":") + 1, string.length()), "0123456789") == -1)
// 		return false;
// 	return true;
// }

// bool message::unReferer(string string, std::string host)
// {
// 	//http://127.0.0.1:4243/page2.html
// 	//make it smaller by directly putting everything in
// 	std::string check;
// 	std::cout << "string ==" << host << std::endl;
// 	if(string.substr(0, 7) != "http://")
// 		return false;
// 	if (string.substr(7, host.length() - 1) == host)
// 		return false;
// 	check = string.substr(host.length() + 6,  string.length());
// 	// std::cout << "check == " << check << std::endl;
// 	if (check == "/")
// 		return true;
// 	std::string root = "./root./" + check;
// 	int _fd = open(root.c_str(), O_DIRECTORY);
// 	if (fd == -1)
// 		std::cout << "path is incorrect" << std::endl;
// 	close(_fd);
// 	string = " ";
// 	host = " ";
// 	return true;
// }

/*

General Header

Request Header

Response Header

Entity Header


GET PUT DELETE POST HEAD


*/
