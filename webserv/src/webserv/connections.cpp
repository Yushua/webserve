#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>

void webserv::connect_new_socket()
{
	/* Don't connect new socket when array is full */
	if (new_socket_count >= SOCKET_COUNT_MAX)
		return;

	/* Connect to new socket */
	socket_t new_socket = accept(welcome_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	
	if (new_socket < 0)
		perror("accept");
	else
	{ /* Add new socket to array */
		new_socket_count++;
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
		sockets[new_socket_count].fd = new_socket;
		sockets[new_socket_count].events = POLLIN;
		sockets[new_socket_count].revents = 0;
#ifdef DEBUG
		cout << GREEN << "  -~={ Connected " << new_socket_count << " }=~-\n" << RESET;
#endif
	}
}

void webserv::disconnect_socket(const int index)
{
#ifdef DEBUG
	cout << RED << "  -~={ Diconnected " << index << " }=~-\n" << RESET;
	if (new_socket_count != index)
		cout << YELLOW << "  -~={ Moved " << new_socket_count << " to " << index << " }=~-\n" << RESET;
#endif

	/* Replace disconnecting socket with the last item in the array */
	/* This is the fastest way to remove an item from an array, without leaving a gap */
	close(sockets[index].fd);
	sockets[index].fd = sockets[new_socket_count].fd;
	new_socket_count--;
}
