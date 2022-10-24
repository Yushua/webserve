#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>

void webserv::connect_new_socket(const int index)
{
	/* Don't connect new socket when array is full */
	if (new_socket_count >= SOCKET_COUNT_MAX)
		return;

	/* Connect to new socket */
	struct SocketInfo_s &sock_info = sockets_info[index];
	socket_t new_socket = accept(sockets[index].fd, (struct sockaddr *)&sock_info.address, (socklen_t*)&sock_info.addrlen);
	
	if (new_socket < 0)
		perror("accept");
	else
	{ /* Add new socket to array */
		new_socket_count++;
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
		sockets[new_socket_count].fd = new_socket;
		sockets[new_socket_count].events = POLLIN | POLLOUT;
		sockets[new_socket_count].revents = 0;
		sockets_info[new_socket_count].listen = false;
		sockets_info[new_socket_count].recieving_from_server = false;
		sockets_info[new_socket_count].msg.reset(new_socket);
#ifdef DEBUG
		cout << GREEN << "  -~={ " << new_socket_count << " connected }=~-\n" << RESET;
#endif
	}
}

void webserv::disconnect_socket(const int index)
{
#ifdef DEBUG
	cout << RED << "  -~={ " << index << " diconnected }=~-\n" << RESET;
	if (new_socket_count != index)
		cout << YELLOW << "  -~={ " << new_socket_count << " moved to " << index << " }=~-\n" << RESET;
#endif

	/* Replace disconnecting socket with the last item in the array */
	/* This is the fastest way to remove an item from an array, without leaving a gap */
	close(sockets[index].fd);
	sockets[index].fd = sockets[new_socket_count].fd;
	sockets_info[index] = sockets_info[new_socket_count];
	new_socket_count--;
}
