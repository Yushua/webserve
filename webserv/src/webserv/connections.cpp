#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>

int webserv::connect_new_socket(const int index)
{
	/* Don't connect new socket when */
	/*  there are no available positions */
	int position = this->tryGetAvailablePosition();
	if (position < 0)
		return -1;

	/* Connect to new socket */
	struct SocketInfo_s &sock_info = sockets_info[index];
	socket_t new_socket = accept(sockets[index].fd, (struct sockaddr *)&sock_info.address, (socklen_t*)&sock_info.addrlen);

	if (new_socket < 0)
		ft_error("connect_new_socket");
	else
	{ /* Add new socket to array */
		if (fcntl(new_socket, F_SETFL, O_NONBLOCK) == -1)
			ft_error("connect_new_socket");
		sockets[position].fd = new_socket;
		sockets[position].events = POLLIN | POLLOUT;
		sockets[position].revents = 0;
		sockets_info[position].send_fd_index = -1;
		sockets_info[position].fd_only = false;
		sockets_info[position].listen = false;
		sockets_info[position].recieving_from_server = false;
		sockets_info[position].msg.reset(new_socket);
		
#ifdef DEBUG
		cout << GREEN << "  -~={ " << position << " connected }=~-" << RESET << '\n';
#endif
	}
	return position;
}

int webserv::connect_new_fd_only(const int index, const int fd)
{
	/* Don't connect new socket when */
	/*  there are no available positions */
	int position = this->tryGetAvailablePosition();
	if (position < 0)
		return -1;

	{ /* Add new socket to array */
		sockets[position].fd = fd;
		sockets[position].events = POLLIN | POLLOUT;
		sockets[position].revents = 0;
		sockets_info[position].send_fd_index = index;
		sockets_info[position].fd_only = true;
		sockets_info[position].listen = false;
	
#ifdef DEBUG
		cout << GREEN << "  -~={ " << position << " fd only }=~-" << RESET << '\n';
#endif
	}
	return position;
}

void webserv::disconnect(const int index)
{
	struct pollfd &poll_fd = sockets[index];
	struct SocketInfo_s &socket = sockets_info[index];

#ifdef DEBUG
	if (socket.msg.getState() == msgError)
		cout << RED << "  -~={ " << index << " diconnected: msgError }=~-" << RESET << '\n';
	else
		cout << RED << "  -~={ " << index << " diconnected }=~-" << RESET << '\n';
#endif

	if (!socket.fd_only && socket.send_fd_index != -1)
		this->disconnect(socket.send_fd_index);

	if (close(sockets[index].fd) == -1)
		ft_error("disconnect");

	poll_fd.fd = numeric_limits<int>::max();
	poll_fd.events = 0;
	socket.msg.reset();

	this->returnPosition(index);
}
