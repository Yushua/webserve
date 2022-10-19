#include <webserv.hpp>

bool webserv::make_sure_messege_is_complete(const int index)
{
	struct SocketInfo_s &sockInfo = sockets_info[index];
	message &msg = sockInfo.msg;

	if (msg.isHeaderComplete() && msg.isBodyComplete()) {
		msg.init(sockets[index].fd);

		/* Client Disconected */
		if (!msg.isHeaderComplete())
			{ this->disconnect_socket(index); return true; }

		/* Check for invalid request */
		if (!msg.isValid()) 
			{ this->send_new_error(index, 400); return true; }

		/* Body too large */
		if (msg.getContentLength() > msg.getConfig().client_body_size)
			{ this->send_new_error(index, 413); return true; }

		debug_print_request(index, msg);

		if (!msg.isBodyComplete())
			return true;
	}

	if (!msg.isBodyComplete()) {
		msg.loadBody();

		if (msg.getBodyLength() > msg.getContentLength())
			{ this->send_new_error(index, 413); return true; }

		if (!msg.isBodyComplete())
			return true;
	}

	if (msg.getBodyLength() < msg.getContentLength())
		{ this->send_new_error(index, 413); return true; }

	return false;
}
