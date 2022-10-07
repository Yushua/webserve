/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unReferer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 10:34:09 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/07 13:43:43 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>
#include <fstream>

#include<iostream>

bool message::unReferer(string string)
{
	//http://127.0.0.1:4243/page2.html
	//make it smaller by directly putting everything in
	if (string.substr(0, 7) != "http://")
		return false;
	if (string.substr(7, this->Host.length() - 1) == this->Host)
		return false;
	std::string check = check = string.substr(this->Host.length() + 6,  string.length());
	if (check == "/")
		return true;
	
	ifstream _file;
	_file.open(check);
	if (!_file.good()) {
		this->send_error(sockets[index].fd, 404);
		this->disconnect_socket(index);
		return;
	}
	return true;
}
