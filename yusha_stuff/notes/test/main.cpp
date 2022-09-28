/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 16:02:35 by ybakker       #+#    #+#                 */
/*   Updated: 2022/09/28 17:52:10 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include "Webserv.hpp"

int main (void)
{
    Webserv webserve(PORT);
    webserve.impliment_socket();
    webserve.run();
    return 0;
}