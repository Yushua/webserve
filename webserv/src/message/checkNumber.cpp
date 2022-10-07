/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkNumber.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 09:43:50 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/07 09:45:46 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>

int message::checkNumber(std::string string, const char *input)
{
	return string.find_first_not_of(input) == string::npos;
}
