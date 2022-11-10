#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <colors.hpp>

void webserv::cmd_GET(const int index, const message &msg) {

	/* File doesn't exist */
	if (!msg.getStatState()) {
		this->send_new_error(index, 404);
		return;
	}

	string requested_file;

	/* Get path and or handle directory */
	if (S_ISDIR(msg.getStat().st_mode)) {
		
		const string &dir_behavior = msg.getConfig().dir_behavior;
		
		/* List dictionary */
		if (dir_behavior == "list") {
			this->send_new(index, "HTTP/1.1 200 OK\n",
				this->generate_index_page(index, msg));
			return;
		}
		/* Permision denied */
		else if (dir_behavior == "error") {
			this->send_new_error(index, 403);
			return;
		}
		
		requested_file = dir_behavior;
	} else
		requested_file = msg.getPath();

	/* Checking if it's a cgi request */
	string extension = ft_get_extension(requested_file);
	map<string, string>::iterator key = cgi_options.find(extension);
	if (key != cgi_options.end()) {
		cgi_get(index, msg, requested_file, key->second);
		return;
	}

	/* Send file */
	this->send_new_file(index, "HTTP/1.1 200 OK\n", requested_file);
}
