/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkDelete.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 15:30:46 by ybakker       #+#    #+#                 */
/*   Updated: 2022/11/10 15:30:56 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>

void message::checkDelete()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	for (; itr != end; ++itr) {
		if (itr->first == "Host:") {
			this->unHost(itr->second);
		}
	}

}
