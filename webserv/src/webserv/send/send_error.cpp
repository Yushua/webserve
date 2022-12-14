#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <colors.hpp>

void webserv::send_new_error(const int index, const int error_code) {

	string headers = "HTTP/1.1 " + ft_to_string(error_code) + '\n';
	
	/* Get error page file, or generate one */
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
		this->send_new(index,
				headers
				+ "Content-Length: "
				+ ft_to_string(default_error_page.length())
				+ "\n\n", fds[0]);
		
#ifdef DEBUG
		cout << RED << "  -~={ error code #" << error_code << " has no page assigned }=~-" << RESET << '\n';
#endif
		return;
	}

	/* Send found header */
	headers += this->header_get_content_type(found->second);
	this->send_new_file(index, headers, found->second);
}

void webserv::send_new_error_fatal(const int index, const int error_code) {

	send_new_error(index, error_code);
	sockets_info[index].disconnect_after_send = true;

}
