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
	int i = strlen("localhost:");
	if (string.substr(i, string.length() - i).find_first_not_of("0123456789\n") != string::npos) {
		this->valid = false;
	}
	else {
		this->valid = true;
	}
}

static std::string find_from_end(std::string path, char c) {
	std::string string = "";
	int i = path.length();
	while (i > 0) {
		if (path[i] == c) {
			break;
		}
		i--;
	}
	i++;
	string = path.substr(i);
	return (string);
}

void webserv::plainText(const int index, message &msg) {
	fstream file;
	std::string fileName;
	std::string pathName;
	if (msg.getPath().find_first_not_of("\\") == string::npos) {
		fileName = "";
		pathName = "root/cgi-bin/";
	}
	else {
		fileName = find_from_end(msg.getPath(), '/');
		pathName = msg.getPath().substr(0, msg.getPath().length() - fileName.length());
	}
	/* get the state which tells me if I need to make something. I need to be sure its not a folder*/
	struct stat info1;
	if (stat(pathName.c_str(), &info1 ) != 0 ) {
    	send_new_error_fatal(index, 404);
		return;
	}
	/* check if the first part is a directory, if else fail*/
	if (!S_ISDIR(info1.st_mode)) {
		send_new_error_fatal(index, 404);
		return;
	}
	int i = 0;
	std::string name;
	while (true) {
		if (i == 0)
			name = pathName + fileName;
		else
			name = pathName + ft_to_string(i) + "_" + fileName;
		std::string cach = pathName + name;
		struct stat info;
		/* check if the first part is a directory, if else fail*/
		/* if file IS THERE, ++*/
		if (stat(name.c_str(), &info) == -1)
			{break;}
		i++;
	}
	if (i == 0)
		fileName = pathName + fileName;
	else
		fileName = pathName + ft_to_string(i) + "_" + fileName;
	/* while loop 
	if this file exists there, then add number, until it succeeds and change the filename into that*/

	/* open filename in that path, put the body in there, close*/
	file.open(fileName.c_str(), fstream::in | fstream::out | fstream::trunc);
	file << msg.getBody();
	file.close();
	this->send_new(index, "HTTP/1.1 201\nContent-Length: 0\n\n", -1);
}

void webserv::cmd_POST(const int index, message &msg) {
	
	map<string, string> _header = msg.getHeaders();
	map<string, string>::iterator itr = _header.begin();
	map<string, string>::iterator end = _header.end();
	std::string store;
	/* setting up the boolians, CGI or cmd_POST */
	bool isCGI = false;
	for (; itr != end; ++itr) {
		/* checking here if the content type says that its CGI */
		if ((itr->first == "Content-Type:")) {
			if (itr->second.find("multipart/form-data; ") != string::npos) {
				vector<std::string> vec;
				vec = splitStringByString(itr->second, "; ");
				/* creating the boundary */
				if (vec[0] == "multipart/form-data") {
					isCGI = true;
					vec[1].replace(0, 9, "");
					store = vec[1];
				}
				else
					{ this->send_new_error_fatal(index, 404); return; }
			}
		}
	}
	map<string, string>::iterator key = cgi_options.find(ft_get_extension(msg.getPath()));
	if (isCGI && msg.isValid())
		{ cgi_post(index, msg, msg.getPath(), key->second, store); }
	/* if its not CGI, then it can be done by plainText, which follows the html_POSt cmd logic */
	else if (!isCGI && msg.isValid())
		{ plainText(index, msg); }
	else
		{ this->send_new_error_fatal(index, 404); return; }
}
