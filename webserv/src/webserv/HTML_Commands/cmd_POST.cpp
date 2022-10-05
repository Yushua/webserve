#include <webserv.hpp>

void webserv::cmd_POST(const int index, const message &msg) {
	(void)index;
	(void)msg;
}

/*

The POST method sends data to a server for processing
Send data to the server for processing.  message bdy

 For
example, consider when you are shopping online at Joe's Hardware and you click on the "submit
purchase" button. Clicking on the button submits a POST request (discussed later) with your credit
card information, and an action is performed on the server on your behalf. In this case, the action is
your credit card being charged for your purchase. 

The POST method was designed to send input data to the server.[3] In practice, it is often used to
support HTML forms. The data from a filled-in form typically is sent to the server, which then
marshals it off to where it needs to go (e.g., to a server gateway program, which then processes it).
Figure 3-10 shows a client making an HTTP request—sending form data to a server—with the POST 

When an HTTP/1.0 client makes a POST request and receives a 302 redirect status code in response, it
will follow the redirect URL in the Location header with a GET request to that URL (instead of
making a POST request, as it did in the original request). 

HTTP/1.0 servers expect HTTP/1.0 clients to do this—when an HTTP/1.0 server sends a 302 status
code after receiving a POST request from an HTTP/1.0 client, the server expects that client to follow
the redirect with a GET request to the redirected URL. 

The confusion comes in with HTTP/1.1. The HTTP/1.1 specification uses the 303 status code to get
this same behavior (servers send the 303 status code to redirect a client's POST request to be followed
with a GET request). 

HTTP clients should not pipeline requests that have side effects (such as POSTs). In general,
on error, pipelining prevents clients from knowing which of a series of pipelined requests
were executed by the server. Because nonidempotent requests such as POSTs cannot safely
be retried, you run the risk of some methods never being executed in error conditions. 

no repeats

One example of a server extension is Microsoft's FrontPage Server Extension (FPSE), which supports
web publishing services for FrontPage authors. FPSE is able to interpret remote procedure call (RPC)
commands sent by FrontPage clients. These commands are piggybacked on HTTP (specifically,
overlaid on the HTTP POST method). For details, see Section 19.1. 

When a user issues a query to a web search-engine gateway, she fills out an HTML form and her
browser sends the form to the gateway, using an HTTP GET or POST request. The gateway program
extracts the search query and converts the web UI query into the expression used to search the full-text
index.[27] 


*/