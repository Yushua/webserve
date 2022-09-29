#include <webserv.hpp>
#include <message.hpp>
#include <colors.hpp>
#include <iostream>

void webserv::handle_request(const int index)
{
	message msg(sockets[index].fd);
	
	if (!msg.isValid()) {
		cout << RED << "  -~={ " << index << " incorrect input }=~-\n" << RESET;
		this->disconnect_socket(index);
		return;
	}

#ifdef DEBUG
	/* Print out request */
	cout << CYAN << "  -~={ " << index << " sent this }=~-\n" << RESET;
	cout << msg << '\n';
#endif

	const string &type = msg.getStartLine().at(0);
	if (type == "HEAD")
		this->cmd_HEAD(index, msg);
	else if (type == "GET")
		this->cmd_GET(index, msg);
	else if (type == "POST")
		this->cmd_POST(index, msg);
	if (type == "DELETE")
		this->cmd_DELETE(index, msg);
	this->disconnect_socket(index);
}
