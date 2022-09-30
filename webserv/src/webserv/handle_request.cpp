#include <webserv.hpp>
#include <message.hpp>
#include <colors.hpp>
#include <iostream>

void webserv::handle_request(const int index)
{
	message msg(sockets[index].fd);
	
	if (!msg.isValid()) {
#ifdef DEBUG
		cout << RED << "  -~={ " << index << " incorrect input }=~-\n" << RESET;
#endif
		this->send_error(sockets[index].fd, 400);
		this->disconnect_socket(index);
		return;
	}

#ifdef DEBUG
	/* Print out request without body */
	cout << CYAN << "  -~={ " << index << " sent this }=~-\n" << RESET;
	
	{/* Print out the first line */
		const string &body = msg.getOriginal();
		int delimiter_position = 0;
		while (body[delimiter_position] != '\n')
			++delimiter_position;
		cout << body.substr(0, delimiter_position) << '\n';
	}

	{/* Print out headers */
		map<string, string>::const_iterator itr = msg.getHeaders().cbegin();
		map<string, string>::const_iterator end = msg.getHeaders().cend();
		for (; itr != end; ++itr)
			cout << itr->first << ": " << itr->second << '\n';
	}
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
	//this->disconnect_socket(index);
}
