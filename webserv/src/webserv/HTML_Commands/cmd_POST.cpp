#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static std::string find_from_end(std::string path, char c) {
	
	for (int i = path.length(); i > 0; --i)
		if (path[i] == c)
			return (path.substr(i + 1));
		
	return "";
}

void webserv::plainText(const int index, message &msg) {

	string directory;
	string original_filename;
	string final_filename;
	
	original_filename = find_from_end(msg.getPath(), '/');
	directory = msg.getPath().substr(0, msg.getPath().length() - original_filename.length());
	final_filename = directory + original_filename;
	
	/* See if file already exists and generate new name if needed */
	size_t i = 0;
	struct stat info;
	while (stat(final_filename.c_str(), &info) != -1)
		final_filename = directory + ft_to_string(++i) + "_" + original_filename;

	{/* Write body to file */
		ofstream file(final_filename.c_str());
		if (!file)
			ft_error("plainText");
		file << msg.getBody();
		file.close();
	}
	
	{/* Send back response */
		#define CHECKED(x) if (x == -1) ft_error("plainText");
		
		int fds[2];
		CHECKED( pipe(fds) );

		string page = "<!DOCTYPE html><html><body><h1>File "
				+ final_filename.substr(directory.length(), string::npos)
				+ " created.</h1></body></html>\n";

		page = "Content-Length: " + ft_to_string(page.length()) + "\n\n" + page;
		
		CHECKED( write(fds[1], page.c_str(), page.length()) );
		CHECKED( close(fds[1]) );
		CHECKED( fcntl(fds[0], O_NONBLOCK) );
		
		this->send_new(index, "HTTP/1.1 201\n", fds[0]);
	}
}

void webserv::cmd_POST(const int index, message &msg) {
	
	map<string, string> _headers = msg.getHeaders();
	
	bool has_cgi_body = false;
	bool is_cgi_file = false;
	
	string Content_Type = msg.getHeader("Content-Type:");
	map<string, string>::iterator Interpreter;

	/* Checking if target is a cgi file */
	if (msg.getStatState() && S_ISREG(msg.getStat().st_mode)) {
		Interpreter = cgi_options.find(ft_get_extension(msg.getPath()));
		is_cgi_file = Interpreter != cgi_options.end();
	}

	/* Checking if Content-Type is for cgi */
	if (is_cgi_file
		&& Content_Type.length() > 21
		&& strncmp(Content_Type.c_str(), "multipart/form-data; ", 21) == 0) {
		
		Content_Type.erase(0, 30);
		has_cgi_body = true;
	}
	
	
	if (has_cgi_body && is_cgi_file)
		cgi_post(index, msg, msg.getPath(), Interpreter->second, Content_Type);
	else
		plainText(index, msg);
}
