#include <webserv.hpp>
#include <message.hpp>
#include <colors.hpp>
#include <iostream>

void webserv::handle_request(const int index)
{	
	message &msg = sockets_info[index].msg;

	if (make_sure_messege_is_complete(index))
		return;

	msg.redirect(*this);

	/* Get method name */
	const string &type = msg.getStartLine().at(0);

	/* See if method is allowed */
	vector<const string>::iterator found = find(
		msg.getConfig().allowed_methods.begin(),
		msg.getConfig().allowed_methods.end(),
		type);
	if (found == msg.getConfig().allowed_methods.end()) {
		this->send_new_error_fatal(index, 403);
		// this->disconnect(index);
		return;
	}

	if (type == "GET")
		this->cmd_GET(index, msg);
	else if (type == "POST")
		this->cmd_POST(index, msg);
	else if (type == "DELETE")
		this->cmd_DELETE(index, msg);
	else
		this->send_new_error(index, 400);
	
	msg.reset();
}
