/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkGet.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 15:29:21 by ybakker       #+#    #+#                 */
/*   Updated: 2022/11/10 15:29:43 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>

void message::checkGet()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	for (; itr != end; ++itr) {
		if (itr->first == "Host:") {
			this->unHost(itr->second);
		}
		else if (itr->first == "Referer") {
			this->unReferer(itr->second);
		}
	}
}
