#include <webserv.hpp>

short ft_cheeky_poll(const int fd) {
	struct pollfd a;
	a.fd = fd;
	a.events = POLLIN | POLLOUT;
	a.revents = 0;
	poll(&a, 1, TIMEOUT);
	return a.revents;
}
