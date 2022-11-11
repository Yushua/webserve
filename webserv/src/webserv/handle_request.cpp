#include <webserv.hpp>
#include <message.hpp>
#include <colors.hpp>
#include <iostream>

void webserv::handle_request(const int index)
{	
	message &msg = sockets_info[index].msg;

	if (make_sure_messege_is_complete(index))
		return;

	/* Redirecting to different server */
	if (msg.getState() == msgRedirect) {

		string new_url = msg.getPath().substr(3, msg.getPath().length() - 3);
		
		this->send_new(index,
			"HTTP/1.1 303\n"
			"Content-Length: 0\n"
			"Location: "
			+ new_url + "\n\n", -1);
		return;
	}

	/* Get method name */
	const string &type = msg.getStartLine().at(0);

	/* See if method is allowed */
	vector<const string>::iterator found = find(
		msg.getConfig().allowed_methods.begin(),
		msg.getConfig().allowed_methods.end(),
		type);
	if (found == msg.getConfig().allowed_methods.end()) {
		if (type == "GET"
			|| type == "POST"
			|| type == "DELETE")
			this->send_new_error_fatal(index, 405); /* Known Method */
		else
			this->send_new_error_fatal(index, 400); /* Unknown Method*/
		return;
	}

	/* Call method */
	if (type == "GET")
		this->cmd_GET(index, msg);
	else if (type == "POST")
		this->cmd_POST(index, msg);
	else if (type == "DELETE")
		this->cmd_DELETE(index, msg);

	msg.reset();
}
