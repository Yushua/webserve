#include <webserv.hpp>
#include <colors.hpp>
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

void webserv::plainText(const int index, message &msg, bool chunk){
	std::cout << "path ==" << msg.getPath() << std::endl;
	ofstream file;
	//if chunk == true, I need to check if this path is a chunk file. or a normal file
	if (msg.getStatState())//need to check if this is a chunk file, meaning it exist because a chunk has been send there
	{
		//if its folder
		if (S_ISDIR(msg.getStat().st_mode)){
			send_new_error_fatal(index, 404)
			return;
		}
		//when it does not exist, create
		file.open(msg.getPath(), fstream::in | fstream::out | fstream::trunc);
		if (!file.good()){
			send_new_error_fatal(index, 404)
			return;
		}
	}
	else{//if stat fails
		send_new_error_fatal(index, 404);
		this->disconnect(index);
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

void webserv::cmd_POST(const int index, message &msg) {
	
	// cout << YELLOW << msg.getHeadersString() << RESET;
	
	map<string, string> _header = msg.getHeaders();
	// map<string, string>::iterator found = _header.find("Content-Length:");
	// if (found != msg.getHeaders().end()) {

	// }
	// else {

	// }


	// map<string, string> _header = msg.getHeaders();
	map<string, string>::iterator itr = _header.begin();
	map<string, string>::iterator end = _header.end();
	std::string store;
	std::cout << "path ====="  << std::endl;
	bool chunk = false;
		//if its cgi, first check if the file is there
	bool isCGI = false;
	for (; itr != end; ++itr){
		std::cout << "first [" << itr->first << "][" << itr->second << std::endl;
		if (itr->first == "Content-Length:"){
			if (msg.getContentLength() != msg.getBody().length()){
				this->send_new_error(sockets[index].fd, 404);
				return;
			}
		}
		else if (itr->first == "Host:")
		{
			std::string tmp = itr->second;
			msg.doUnHost(tmp);
			if (msg.isValid() == false){
				this->send_new_error(sockets[index].fd, 404);
				return;
			}
		}
		else if ((itr->first == "Transfer-Encoding:" || itr->first == "TE:" ) && itr->second.find("chunked")){
			if (unchunkCheck(msg.getBody()) == false){
				this->send_new_error(sockets[index].fd, 404);
				return;
			}
			//if true, put the chunk message in the file
			chunk = true;
		}
		else if ((itr->first == "Content-Type:")){
			//use chunks
			vector<std::string> vec;//store the split line
			vec = configSplit(itr->second, "; ");
			if (vec[0] == "multipart/form-data"){
				isCGI = true;
				vec[1].replace(0, 9, "");
				store = vec[1];
			}
			std::cout << "message == " << itr->second << std::endl;
			isCGI = true;
		}
	}
	if (isCGI == true){
		string extension = ft_get_extension(msg.getPath());
		map<string, string>::iterator key = cgi_options.find(extension);
		cgi_post(index, msg, msg.getPath(), key->second, store);
	}
	else{
		plainText(index, msg, chunk);
	}
}

/*
biggest problem now is, that, when a chunk gets in. FIRST gets in,  need to save this chunk and keep using it.

we have to look into how many uploads we can do, i COULD make multiple ones, but that leads to a but of a problem due to the multiple servers.
a global map<std::string name, int fd> would solve this. if we are going to use mulithreading then this
is the place, to palce mutexes to protect the use of it. I don't want more than one server to touch it.

with a normal, NOT chunk message. its ok.

i first check if the first message is a chunk and make sure to store that in the global map
then when it reaches the end, and I don't find chunk, I know I have to then remove it from that global map. if then after I get another chunk with that message
it would just give the "access denied" error.

problem with multiple servers is that they need to know that, one, that path can't be used. so when I check if its not there, I also make it
two- i have a chunk file, I store the linl. ubut another file ALSO uses the same path and ALSO has that chunk. then two servers are sending chunks TO THE
SAME FILE. i need to make sure that OTHER servers can't use the chunk, while still keep record of that this is a chunk file and that this server can send chunks to it
a simple way is to check, that when a link is sued in a server for the first time. that it isn't used as a chunk, and it isn't open

this way, even fi the file is a chunk file, the other servers can't open it, because when chunk, THE FIRST CHUNK, oly gets accepted if the file doesn't exist.
*/
