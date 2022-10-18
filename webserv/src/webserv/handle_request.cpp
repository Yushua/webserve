#include <webserv.hpp>
#include <message.hpp>
#include <colors.hpp>
#include <iostream>

void webserv::handle_request(const int index)
{
	message msg(sockets[index].fd);

#ifdef DEBUG
	debug_print_request(index, msg);
#endif

	/* Client Disconected */
	if (msg.getOriginal().length() == 0) {
		this->disconnect_socket(index);
		return;
	}
	
	/* Check for invalid request */
	if (!msg.isValid()) {
		this->send_new_error(index, 400);
		return;
	}

	msg.redirect(*this);

	/* Get method name */
	const string &type = msg.getStartLine().at(0);
	
	/* See if method is allowed */
	vector<const string>::iterator found = find(
		msg.getConfig().allowed_methods.begin(),
		msg.getConfig().allowed_methods.end(),
		type);
	if (found == msg.getConfig().allowed_methods.end()) {
		this->send_new_error(index, 403);
		return;
	}

	if (type == "GET")
		this->cmd_GET(index, msg);
	else if (type == "POST")
		this->cmd_POST(index, msg);
	// else if (type == "HEAD")
	// 	this->cmd_HEAD(index, msg);
	else if (type == "DELETE")
		this->cmd_DELETE(index, msg);
}
