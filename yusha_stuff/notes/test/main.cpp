/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 16:02:35 by ybakker       #+#    #+#                 */
/*   Updated: 2022/09/28 16:29:37 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include "Webserv.hpp"

int main (void)
{
    Webserv webserve(PORT);
    webserve.run();
    return 0;
}