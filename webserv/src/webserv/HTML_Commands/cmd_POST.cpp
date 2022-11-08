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
	if (string.substr(i, string.length() - i).find_first_not_of("0123456789\n") != string::npos){
		this->valid = false;
	}
	else{
		this->valid = true;
	}
}

void webserv::plainText(const int index, message &msg, std::string store){
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
	/* get the name of the path */
	std::string filename = "filename=\"" + msg.getPath() + "\"";


	std::cout << "==plainText==\npath ==" << msg.getPath() << std::endl;
	std::cout << YELLOW << msg.getBody() << RESET << std::endl;
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
	std::cout << "store[" << store << "]\n";
	int i = index;
	i++;
	/*
	------WebKitFormBoundaryzStxly5tvEnSHxLf
	Content-Disposition: form-data; name="fileToUpload"; filename=""
	
	Content-Type: application/octet-stream


	------WebKitFormBoundaryzStxly5tvEnSHxLf--
	*/

	/*

	*/
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
	std::string Content_Disposition = "Content-Disposition: form-data;";
	std::string name = "name=\"fileToUpload\";";;
	/* get the name of the path */
	std::string filename = "filename=\"" + msg.getPath() + "\"";
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
				store = itr->second;
			}
		}
	}
	/* chunk is checked inside of plainText*/
	string extension = ft_get_extension(msg.getPath());
	map<string, string>::iterator key = cgi_options.find(extension);
	if (isCGI == true && msg.isValid() == true){
		cgi_post(index, msg, msg.getPath(), key->second, store);
	}
	else if (isPLain == true){
		plainText(index, msg, store);
		std::cout << "plain text start" << std::endl;
		// cgi_post_string(Content_Disposition + " " + name + " " + filename + "\n", "Content-Type: " + store + "\n",
		// index, msg, msg.getPath(), key->second);
		std::cout << "plain text success" << std::endl;
	}
	else
	{
		std::cout << "POST failed to find a Content-Type\n"; 
		this->send_new_error_fatal(index, 404);
		return;
	}
	std::cout << "end POST\n"; 
}
