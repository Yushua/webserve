#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static bool unchunkCheck(std::string string){
	bool chunkStatus = false;
	std::string tmp;
	int y = 0;
	int i = 0;
	int len = string.length();
	int start = 0;
	/*
	because chunk is
	number
	string
	
	I compare the first string as a nb, then the next as a string.
	after a number there needs to be a string
	*/
	while (i < len){
		start = i;
		i = string.find("\r");
		tmp = string.substr(start, i - start);/* taking everything after localhost: and look into 4242*/
		if (chunkStatus == false){
			if (tmp.find_first_not_of("0123456789") == string::npos){
				return false;
			}
			y = atoi(tmp.c_str());
			if (y == 0)
				return true;
			chunkStatus = true;
		}
		else if (chunkStatus == true){
			if (static_cast<unsigned long>(y) != tmp.length()){
				return false;
			}
			chunkStatus = false;
		}
		i += 2;
	}
	if (chunkStatus == true){
		return false;
	}
	return true;
}

// void message::checkHost(string string)
// {
// 	//127.0.0.1:4243
// 	// std::string tmp = string.substr(0, string.find(":"));
// 	int ip = 0;
// 	int i = 0;
// 	//check for defaulthost
// 	while (string.find(".") != string::npos)
// 	{
// 		i = string.find(".");
// 		if(checkNumber(string, "0123456789") != -1){
// 			// std::cout << check << std::endl;
// 			this->valid = false;
// 		}
// 		string.erase(0, i+1);
// 		ip++;
// 	}
// 	if (string.find(":") != string::npos){
// 		i = string.find(":");
// 		if(checkNumber(string, "0123456789") != -1){
// 			// std::cout << check << std::endl;
// 			this->valid = false;
// 		}
// 		ip++;
// 	}
// 	if (ip != 4)
// 		this->valid = false;
//     this->hostName = string;
// 	// this->valid = true;
// }

void message::checkHost(string string)
{
	//localhost:4242
	// std::string tmp = string.substr(0, string.find(":"));
	int i = strlen("localhost:");
	std::string tmp = string.substr(i, string.length() - i);
	std::cout << "print[" << tmp << std::endl;
	this->valid = true;
}



void webserv::plainText(const int index, message &msg, bool chunk){
	fstream file;
	/* get the state which tells me if I need to make something. I need to be sure its not a folder*/
	if (msg.getStatState())
	{
		/* checking if its a folder, if so, false */
		if (S_ISDIR(msg.getStat().st_mode))
			{ send_new_error_fatal(index, 404); return; }
		/* if not folder, then check if its a true path */
		file.open(msg.getPath(), fstream::in | fstream::out | fstream::trunc);
		if (!file.good())
		{ send_new_error_fatal(index, 404); return; }
	}
	else /* if stat fails */
		{ send_new_error_fatal(index, 404); this->disconnect(index); return;}
	file << msg.getBody();
	file.close();
	std::cout << "plain text success" << std::endl;
}

void webserv::cmd_POST(const int index, message &msg) {
	
	map<string, string> _header = msg.getHeaders();
	map<string, string>::iterator itr = _header.begin();
	map<string, string>::iterator end = _header.end();
	std::string store;
	std::cout << "==start of POST=="  << std::endl;

	/* setting up the boolians, seeing if there is a chunk or if there is a CGI or Plaintext*/
	bool isCGI = false;
	bool isPLain = false;
	for (; itr != end; ++itr){
		if (itr->first == "Host:")
		{
			std::string tmp = itr->second;
			if (tmp.find("localhost:") != string::npos){
				msg.checkHost(tmp);}
			else{
				msg.doUnHost(tmp);}
			if (msg.isValid() == false){
				this->send_new_error(sockets[index].fd, 404);
				return;
			}
		}
		/* checking here if the content type says that its CGI */
		else if ((itr->first == "Content-Type:")){
			//use chunks
			vector<std::string> vec;
			vec = configSplit(itr->second, "; ");
			if (vec[0] == "text/plain"){
				isPLain = true;}
			else if (vec[0] == "multipart/form-data"){
				isCGI = true;
				vec[1].replace(0, 9, "");
				store = vec[1];
			}
		}
	}
	/* chunk is checked inside of plainText*/
	if (isCGI == true && msg.isValid() == true){
		string extension = ft_get_extension(msg.getPath());
		map<string, string>::iterator key = cgi_options.find(extension);
		cgi_post(index, msg, msg.getPath(), key->second, store);
	}
	else if (isPLain == true){
		plainText(index, msg, chunk);
	}
	else
	{
		this->send_new_error(sockets[index].fd, 404);
		return;
	}
}
