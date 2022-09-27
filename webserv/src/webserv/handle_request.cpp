#include <webserv.hpp>
#include <message.hpp>
#include <colors.hpp>
#include <iostream>

/* The first page of an example website as a raw HTML message */
string page1 = "HTTP/1.1 200 OK\n\n\
<!DOCTYPE html><html><body>\n\
<h1>Welcome!</h1>\n\
<p>This is my server!</p>\n\
<a href=\"lol\">Go somewhere far beyond!</a>\n\
</body></html>";

/* The second page of an example website as a raw HTML message */
string page2 = "HTTP/1.1 200 OK\n\n\
<!DOCTYPE html><html><body>\n\
<h1>Page 2</h1>\n\
<p>Ok, this is a little much to do by hand...</p>\n\
<a href=\"/\">Go back</a></body></html>";

void webserv::handle_request(int index)
{
	message msg(sockets[index].fd);
	
	// if (!msg.check()) {
	// 	cout << RED << "  -~={ " << index << " incorrect input }=~-\n" << RESET;
	// 	this->disconnect_socket(index);
	// 	return;
	// }
	
	/* Print out request */
	cout << CYAN << "  -~={ " << index << " sent this }=~-\n" << RESET;
	cout << msg << '\n';

	if (msg.getStartLine().at(0) == "GET") {
		if (msg.getStartLine().at(1) == "/lol")
			this->send(sockets[index].fd, page2);
		else
			this->send(sockets[index].fd, page1);
		
		/* Close conection after data is sent */
		this->disconnect_socket(index);
		// Maybe we don't need this???
		// Keeping it here just in case.
	}
}
