#include <webserv.hpp>

bool webserv::make_sure_messege_is_complete(const int index)
{
	struct SocketInfo_s &sockInfo = sockets_info[index];
	message &msg = sockInfo.msg;

	if (msg.isHeaderComplete() && msg.isBodyComplete()) {
		msg.init(sockets[index].fd);

		/* Client Disconected */
		if (msg.getOriginal().length() == 0) {
			this->disconnect_socket(index);
			return true;
		}

		/* Check for invalid request */
		if (!msg.isValid()) {
			this->send_new_error(index, 400);
			return true;
		}

		/* !!! HANDLE PROPERLY !!! */
		/* Body too large */
		if (msg.getContentLength() > msg.getConfig().client_body_size) {
			this->disconnect_socket(index);
			return true;
		}

		debug_print_request(index, msg);

		if (!msg.isBodyComplete())
			return true;
	}

	if (!msg.isBodyComplete()) {
		msg.loadBody();

		/* !!! HANDLE PROPERLY !!! */
		if (msg.getBody().length() > msg.getContentLength()) {
			this->disconnect_socket(index);
			return true;
		}

		if (!msg.isBodyComplete())
			return true;
	}

	/* !!! HANDLE PROPERLY !!! */
	if (msg.getBody().length() < msg.getContentLength()) {
		this->disconnect_socket(index);
		return true;
	}

	return false;
}
