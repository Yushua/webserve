#include <webserv.hpp>
#include <colors.hpp>

#define RETURN_TO_POLL true
#define CONTINUE false

bool webserv::make_sure_messege_is_complete(const int index)
{
	struct SocketInfo_s &sockInfo = sockets_info[index];
	message &msg = sockInfo.msg;

	switch (msg.getState()) {

		case ready:
			return CONTINUE;
		
		case msgError:
			return RETURN_TO_POLL;


		case loadingHeaders:
			msg.loadHeaders();

			/* Client Disconected */
			if (msg.getHeadersString().length() == 0)
				{ this->disconnect_socket(index); return true; }

			/* Return to poll if headers aren't complete */
			if (msg.getState() == loadingHeaders)
				return RETURN_TO_POLL;
			
			msg.init();

			/* Check if message is valid */
			if (!msg.isValid()) {
				msg.reset();
				this->send_new_error(index, 400);
				return RETURN_TO_POLL;
			}

			/* Return to poll if body isn't complete */
			if (msg.getState() == loadingBody)
				return RETURN_TO_POLL;
			

			/* All good to go! */
			return CONTINUE;


		case loadingBody:
			msg.loadBody();

			/* Check if body doesn't exeed Content_length */
			if (msg.getBody().length() > msg.getContentLength()) {
				this->send_new_error(index, 413);
				return RETURN_TO_POLL;
			}

			/* Return to poll if body isn't complete */
			if (msg.getState() == loadingBody)
				return RETURN_TO_POLL;
		
			/* Check if body matches Content_length */
			if (msg.getBody().length() != msg.getContentLength()) {
				this->send_new_error(index, 413);
				return RETURN_TO_POLL;
			}

			/* All good to go! */
			return CONTINUE;


		/* What??? How??? */
		default:
			cerr << RED << " <{[ Learn to C++ ma dude! ]}>\n" << RESET;
			exit(1);
	}
}
