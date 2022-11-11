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
		
		case msgRedirect:
		case msgError:
			return RETURN_TO_POLL;

		case loadingHeaders:
			msg.loadHeaders();

			/* Client Disconected or Error */
			if (msg.getState() == msgError
				|| msg.getHeadersString().length() == 0)
				{ this->disconnect(index); return RETURN_TO_POLL; }

			/* Return to poll if headers aren't complete */
			if (msg.getState() == loadingHeaders)
				return RETURN_TO_POLL;
			
			msg.init();
			msg.redirect(*this);
			if (msg.getState() == msgRedirect)
				return CONTINUE;

			/* Check if message is valid */
			if (!msg.isValid()) {
				msg.reset();
				this->send_new_error_fatal(index, 400);
				return RETURN_TO_POLL;
			}

			debug_print_request(index, msg);

			if (msg.isChunked()) {
				msg.tryDechunk();
				
				/* Disconected Error */
				if (msg.getState() == msgError)
					{ this->disconnect(index); return RETURN_TO_POLL; }
			}

			/* Return to poll if body isn't complete */
			if (msg.getState() == loadingBody)
				return RETURN_TO_POLL;

			/* All good to go! */
			return CONTINUE;


		case loadingBody:
			msg.loadBody();

			/* Disconect Error */
			if (msg.getState() == msgError)
				{ this->disconnect(index); return RETURN_TO_POLL; }

			/* Body too large for server */
			if (msg.getReadAmount() > msg.getConfig().client_body_size) {
				this->send_new_error_fatal(index, 413);
				return RETURN_TO_POLL;
			}

			if (msg.isChunked()) {
				msg.tryDechunk();
				
				/* Disconect Error */
				if (msg.getState() == msgError)
					{ this->disconnect(index); return RETURN_TO_POLL; }
				
				/* Return to poll if body isn't complete */
				if (msg.getState() == loadingBody)
					return RETURN_TO_POLL;

				/* All good to go! */
				return CONTINUE;
			}

			/* Check if body doesn't exeed Content_length */
			if (msg.getBody().length() > msg.getContentLength()) {
				this->send_new_error_fatal(index, 400);
				return RETURN_TO_POLL;
			}

			/* Check if body is complete */
			if (msg.getBody().length() < msg.getContentLength())
				return RETURN_TO_POLL;

			/* All good to go! */
			msg.setState(ready);
			return CONTINUE;

	}
}
