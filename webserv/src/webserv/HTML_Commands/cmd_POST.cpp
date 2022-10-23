#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static bool unchunkCheck(std::string string)
{
	// std::string string = "4\r\nWiki\r\n6\r\npedia \r\n3\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n";
	bool chunkStatus = false;
	std::string tmp;
	int y = 0;
	int i = 0;
	int len = string.length();
	int start = 0;
	while (i < len){
		start = i;
		i = string.find("\r");
		tmp = string.substr(start, i - start);
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
	return true;
}

void webserv::cmd_POST(const int index, message &msg) {
	map<string, string> _header = msg.getHeaders();
	map<string, string>::iterator itr = _header.begin();
	map<string, string>::iterator end = _header.end();

	bool chunk = false;
	for (; itr != end; ++itr){
		if (itr->first == "Content-Length:"){
			if (msg.getContentLength() != strlen(msg.getBody())){
				this->send_new_error(sockets[index].fd, 404);
				this->disconnect_socket(index);
				return;
			}
		}
		else if (itr->first == "Host:")
		{
			std::string tmp = itr->second;
			msg.doUnHost(tmp);
			if (msg.isValid() == false){
				this->send_new_error(sockets[index].fd, 404);
				this->disconnect_socket(index);
				return;
			}
		}
		else if ((itr->first == "Transfer-Encoding:" || itr->first == "TE:" ) && itr->second.find("chunked")){
			if (unchunkCheck(msg.getBody()) == false){
				this->send_new_error(sockets[index].fd, 404);
				this->disconnect_socket(index);
				return;
			}
			//if true, put the chunk message in the file
			chunk = true;
		}
	}	
	struct stat file_info;
	/*
	The request succeeded, and a new resource was created as a result.
	This is typically the response sent after POST requests, or some PUT requests.
	
	what do they mean wiht new resource?
	*/
	// if (msg.getPath() == "")
	// {
	// }
	std::cout << "======empty=====" << std::endl;
	std::cout << msg.getPath() << std::endl;
	ofstream file;
	if (stat(msg.getPath().c_str(), &file_info) == -1)
	{
		//create
		file.open("root/cgi-bin/file", fstream::in | fstream::out | fstream::trunc);
		if (!file.good()) {
			this->send_new_error(sockets[index].fd, 404);
			this->disconnect_socket(index);
			return;
		}
	}
	else{//if it does exist, corrupt file, can't override the file
		this->send_new_error(sockets[index].fd, 404);
		this->disconnect_socket(index);
		return;
	}
	std::string string = msg.getBody();
	std::cout << msg.getBody() << std::endl; //nothing in the body yet
	if (chunk == true){
		bool chunkStatus = false;
		std::string tmp;
		int i = 0;
		int len = string.length();
		int start = 0;
		while (i < len){
			start = i;
			i = string.find("\r");
			if (chunkStatus == false){//when number
				if (string.substr(start, i - start) == "0")
					break;
				chunkStatus = true;
			}
			else if (chunkStatus == true){//when input
				chunkStatus = false;
				std::cout << "message[" << string.substr(start, i - start) << "]\n";
				file << string.substr(start, i - start);
			}
			i += 2;
		}	
	}
	else
		file << msg.getBody();
	file.close();
	std::cout << "file uploaded" << std::endl;
}

/*
so how does uplaoding work?

if the file does not exist, make it, and then fill it in
but if the file does exist, delete it ONCE, and then fill it in. or, jsut add to it?
but how o i know, with chunks. if get multiple chunks, then, oeps, ikeep deleting the file.
so with chunks, if it is there. I need to, for the first time, delete the file, and then keep adding to it.
so for each fiel the chunk is set to, I need to also remember if it is the first time.

scenario

imagine I send five chunks. this can all come from the same client. like imagine a chaotic mess of letters I need to send
each letter is send IN THE RIGHT ORDER.
so these five elters ahve all different adresses, i need to store this adress, and as soon as I get the first letter. I say "ok, start this file."
this way I don't delte the file if another letter comes in.
*/
