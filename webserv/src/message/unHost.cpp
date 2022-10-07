/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unHost.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 10:27:32 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/07 10:33:33 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>

bool message::unHost(string string)
{
	//127.0.0.1:4243
    this->Host = string;
	return true;
}
