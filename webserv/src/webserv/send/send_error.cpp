#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <colors.hpp>

void webserv::send_new_error(const int index, const int error_code) {

	string headers = "HTTP/1.1 " + ft_to_string(error_code) + '\n';
	map<int, string>::iterator found = error_pages.find(error_code);
	if (found == error_pages.end()) {
		int fds[2];
		if (pipe(fds) == -1)
			ft_error("send_new_error");
		
		string default_error_page
			= "<!DOCTYPE html><html><body><h1>"
			+ ft_to_string(error_code)
			+ "</h1></body></html>\n";
		
		if (write(fds[1], default_error_page.c_str(), default_error_page.length()) == -1)
			ft_error("send_new_error");

		if (close(fds[1]) == -1)
			ft_error("send_new_error");
		if (fcntl(fds[0], O_NONBLOCK) == -1)
			ft_error("send_new_error");
		this->send_new(index, headers + '\n', fds[0]);
		/*for the content lenght*/
		sockets_info[index].disconnect_after_send = true;
		
#ifdef DEBUG
		cout << RED << "  -~={ error code #" << error_code << " has no page assigned }=~-\n" << RESET;
#endif
		return;
	}
	string &error_page = found->second;

	headers += this->header_get_content_type(error_page);

	this->send_new_file(index, headers, error_page);

	sockets_info[index].disconnect_after_send = true;
}

void webserv::send_new_error_fatal(const int index, const int error_code) {

	send_new_error(index, error_code);
	sockets_info[index].disconnect_after_send = true;

}
