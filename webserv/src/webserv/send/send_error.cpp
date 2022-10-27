#include <webserv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <colors.hpp>

void webserv::send_new_error(const int index, const int error_code) {

	string headers = "HTTP/1.1 " + ft_to_string(error_code) + '\n';
	
	map<int, string>::iterator found = error_pages.find(error_code);
	if (found == error_pages.end()) {
		::send(sockets[index].fd, headers.c_str(), headers.length(), 0);
		this->disconnect(index);
		
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

	sockets_info[index].msg.setState(msgError);

	send_new_error(index, error_code);

}
