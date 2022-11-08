#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

void webserv::plainText(const int index, message &msg){
	ofstream file;
	std::cout << YELLOW << "start pain text" << RESET << std::endl;
	std::cout << YELLOW << msg.getPath() << RESET << std::endl;

	std::string filename = "filename=\"" + msg.getPath() + "\"";
	int i = index;
	i++;
	/* get the state which tells me if I need to make something. I need to be sure its not a folder*/
	// struct stat info;
	// if( stat(pathname, &info ) != 0 )
    // 	printf( "cannot access %s\n", pathname );
	// /* check if the first part is a directory, if else fail*/
	// if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows 
	// 	printf( "%s is a directory\n", pathname );
	// else
	// 	printf( "%s is no directory\n", pathname );

	// /* while loop 
	// if this file exists there, then add number, until it succeeds and change the filename into that*/

	// /* open filename in that path, put shit in there, close*/
	// file << msg.getBody();
	// file.close();
}

void webserv::cmd_POST(const int index, message &msg) {
	
	map<string, string> _header = msg.getHeaders();
	map<string, string>::iterator itr = _header.begin();
	map<string, string>::iterator end = _header.end();
	std::string store;
	std::cout << "==start of POST=="  << std::endl;

	/* setting up the boolians, seeing if there is a chunk or if there is a CGI or Plaintext*/
	bool isCGI = false;
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
		}
	}
	/* chunk is checked inside of plainText*/
	string extension = ft_get_extension(msg.getPath());
	map<string, string>::iterator key = cgi_options.find(extension);
	if (isCGI == true && msg.isValid() == true){
		cgi_post(index, msg, msg.getPath(), key->second, store);
	}
	else{
		plainText(index, msg);
		std::cout << "plain text start" << std::endl;
		// cgi_post_string(Content_Disposition + " " + name + " " + filename + "\n", "Content-Type: " + store + "\n",
		// index, msg, msg.getPath(), key->second);
		std::cout << "plain text success" << std::endl;
	}
	std::cout << "end POST\n"; 
}
