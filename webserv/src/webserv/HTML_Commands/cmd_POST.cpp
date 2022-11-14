#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

#define CHECKED(x) if (x == -1) ft_error("plainText");

void webserv::plainText(const int index, message &msg) {
	fstream file;
	std::string fileName;
	std::string directory;
	if (msg.getPath().find_first_not_of("\\") == string::npos) {
		fileName = "";
		directory = "root/cgi-bin/";
	}
	else {
		fileName = find_from_end(msg.getPath(), '/');
		directory = msg.getPath().substr(0, msg.getPath().length() - fileName.length());
	}
	int i = 0;
	std::string name;
	while (true) {
		if (i == 0)
			name = directory + fileName;
		else
			name = directory + ft_to_string(i) + "_" + fileName;
		std::string cach = directory + name;
		struct stat info;
		/* check if the first part is a directory, if else fail */
		/* if file IS THERE, ++ */
		if (stat(name.c_str(), &info) == -1)
			{break;}
		i++;
	}
	if (i == 0)
		fileName = directory + fileName;
	else
		fileName = directory + ft_to_string(i) + "_" + fileName;
	/* while loop 
	if this file exists there, then add number, until it succeeds and change the filename into that*/

	/* open filename in that path, put the body in there, close*/
	file.open(fileName.c_str(), fstream::in | fstream::out | fstream::trunc);
	if (!file)
		ft_error("plainText");
	file << msg.getBody();
	file.close();
	
	int fds[2];
	CHECKED( pipe(fds) );

	string page = "<!DOCTYPE html><html><body><h1>File "
			+ fileName.substr(directory.length(), string::npos)
			+ " created.</h1></body></html>\n";

	page = "Content-Length: " + ft_to_string(page.length()) + "\n\n" + page;
	
	CHECKED( write(fds[1], page.c_str(), page.length()) );
	CHECKED( close(fds[1]) );
	CHECKED( fcntl(fds[0], O_NONBLOCK) );
	
	this->send_new(index, "HTTP/1.1 201\n", fds[0]);
}

void webserv::cmd_POST(const int index, message &msg) {
	
	map<string, string> _headers = msg.getHeaders();
	
	bool has_cgi_body = false;
	bool is_cgi_file = false;
	
	map<string, string>::iterator Content_Type = _headers.find("Content-Type:");
	map<string, string>::iterator Interpreter;

	if (!msg.getStatState())
		{ this->send_new_error(index, 404); return; }

	/* Checking if target is a cgi file */
	if (S_ISREG(msg.getStat().st_mode)) {
		Interpreter = cgi_options.find(ft_get_extension(msg.getPath()));
		is_cgi_file = Interpreter != cgi_options.end();
	}

	/* Checking if Content-Type is for cgi */
	if (is_cgi_file
		&& Content_Type != _headers.end()
		&& strncmp(Content_Type->second.c_str(), "multipart/form-data; ", 21) == 0) {
		
		Content_Type->second.erase(0, 30);
		has_cgi_body = true;
	}
	
	
	if (has_cgi_body && is_cgi_file)
		cgi_post(index, msg, msg.getPath(), Interpreter->second, Content_Type->second);
	else
		plainText(index, msg);
}
