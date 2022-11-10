/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unReferer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 10:34:09 by ybakker       #+#    #+#                 */
/*   Updated: 2022/11/10 15:34:47 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>
#include <fstream>

#include<iostream>

void message::unReferer(string string)
{
	//http://127.0.0.1:4243/page2.html
	//make it smaller by directly putting everything in
	if (string.substr(0, 7) != "http://")
		this->valid = false;
	if (string.substr(7, this->hostName.length() - 1) == this->hostName)
		this->valid = false;
	std::string check = string.substr(this->hostName.length() + 6,  string.length());
	if (check == "/")
		this->valid = true;
	
	ifstream _file;
	_file.open(check);
	if (!_file.good()) {
		this->valid = false;
	}
	this->valid = true;
}
