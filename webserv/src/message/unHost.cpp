/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unHost.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 10:27:32 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/07 16:04:38 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>

void message::unHost(string string)
{
	//127.0.0.1:4243
	// std::string tmp = string.substr(0, string.find(":"));
	int ip = 0;
	int i = 0;
	//check for defaulthost
	while (string.find(".") != string::npos)
	{
		i = string.find(".");
		if(checkNumber(string, "0123456789") != -1){
			// std::cout << check << std::endl;
			this->valid = false;
		}
		string.erase(0, i+1);
		ip++;
	}
	if (string.find(":") != string::npos){
		i = string.find(":");
		if(checkNumber(string, "0123456789") != -1){
			// std::cout << check << std::endl;
			this->valid = false;
		}
		ip++;
	}
	if (ip != 4)
		this->valid = false;
    this->Host = string;
	this->valid = true;
}
