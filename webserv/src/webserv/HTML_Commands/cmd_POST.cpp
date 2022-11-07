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

void message::checkHost(string string)
{
	//localhost:4242
	int i = strlen("localhost:");
	// std::string tmp = string.substr(i, string.length() - i);
	std::cout << "print host[" << string.substr(i, string.length() - i) << "]" << std::endl;
	if (string.substr(i, string.length() - i).find_first_not_of("0123456789\n") != string::npos){
		this->valid = false;
	}
	else{
		this->valid = true;
	}
	std::cout << "value == " << true << " " << this->valid << std::endl;
}

void webserv::plainText(const int index, message &msg, bool chunk){
	/*
	seperate CGI_POST so it handles the fork in a seperate function
	one with using a a, and B location
		this one is the normal CG
	another using a string
		this one is the header and body that I create
		make the header
		the body

		everything else is the same
	*/
	std::cout << "==plainText==\npath ==" << msg.getPath() << std::endl;
	std::cout << YELLOW << msg.getBody() << RESET << std::endl;
	ofstream file;
	/* get the state which tells me if I need to make something. I need to be sure its not a folder*/
	if (msg.getStatState())
	{
		/* checking if its a folder, if so, false */
		if (S_ISDIR(msg.getStat().st_mode)){
			send_new_error_fatal(index, 404);
			return;
		}
		/* if not folder, then check if its a true path */
		file.open(msg.getPath(), fstream::in | fstream::out | fstream::trunc);
		if (!file.good()){
			send_new_error_fatal(index, 404);
			return;
		}
	}
	else{//if stat fails
		send_new_error_fatal(index, 404);
		this->disconnect(index);
		return;
	}
	if (chunk == true){
		/* create chunk, needs to be remade due to the new POST test method*/
		chunk = false;
	}
	else
		file << msg.getBody();
	file.close();
	std::cout << "plain text success" << std::endl;
}

/*
Content-Disposition: form-data; name="fileToUpload"; filename="chunk.txt"
Content-Type: text/plain
*/
void webserv::cmd_POST(const int index, message &msg) {
	
	map<string, string> _header = msg.getHeaders();
	map<string, string>::iterator itr = _header.begin();
	map<string, string>::iterator end = _header.end();
	std::string store;
	std::cout << "==start of POST=="  << std::endl;

	/* setting up the boolians, seeing if there is a chunk or if there is a CGI or Plaintext*/
	bool chunk = false;
	bool isCGI = false;
	bool isPLain = false;
	for (; itr != end; ++itr){
		std::cout << "[" << itr->first << "][" << itr->second << "]\n";
		/* checking to see if the content-lenght is correct*/
		if (itr->first == "Content-Length:"){
			if (msg.getContentLength() != msg.getBody().length()){
				this->send_new_error_fatal(index, 404);
				return;
			}
		}
		/* checking to see if the host is correct*/
		else if (itr->first == "Host:")
		{
			std::string tmp = itr->second;
			if (tmp.find("localhost:") != string::npos){
				msg.checkHost(tmp);}
			else{
				msg.doUnHost(tmp);}
			if (msg.isValid() == false){
				this->send_new_error_fatal(index, 404);
				return;
			}
		}
		/* if there is a chunked then here its checked if its there and if things are working fine */
		else if ((itr->first == "Transfer-Encoding:" || itr->first == "TE:" ) && itr->second.find("chunked")){
			if (unchunkCheck(msg.getBody()) == false){
				this->send_new_error_fatal(index, 404);
				return;
			}
			//if true, put the chunk message in the file
			chunk = true;
		}
		/* checking here if the content type says that its CGI */
		else if ((itr->first == "Content-Type:")){
			//use chunks
			if (itr->second.find("multipart/form-data; ") != string::npos){
				vector<std::string> vec;
				vec = configSplit(itr->second, "; ");
				if (vec[0] == "multipart/form-data"){//i am creating the boundary
					isCGI = true;
					vec[1].replace(0, 9, "");
					store = vec[1];
				}
				else{
					this->send_new_error_fatal(index, 404);
					return;
				}
			}
			else {
				isPLain = true;
			}
			std::cout << "hello" << store << std::endl;
		}
	}
	/* chunk is checked inside of plainText*/

	std::cout << "==check where==[" << isCGI << "][" << isPLain << "]" << std::endl;
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
		std::cout << "POST failed\n"; 
		this->send_new_error_fatal(index, 404);
		return;
	}
	std::cout << "end POST\n"; 
}
