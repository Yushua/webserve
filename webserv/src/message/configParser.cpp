/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   configParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 09:43:50 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/10 14:24:10 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>
#include <message.hpp>

//make own class

void configParser(map<string, webserv> &bigacontyantnas)
{
    /* Read from file */
    // ifstream file(PATH);
    // stringstream buffer;
    // buffer << file.rdbuf();
    // string data = buffer.str();

    //first line is name
    /*
        listen: = port
        cgi:
        error_page:
        /: paths

        two empty lines

    server.config_listen_to_port(4242);
	server.config_listen_to_port(4243);
	server.config_add_cgi_option("py", "/usr/bin/python");
	server.config_add_cgi_option("lol", "");
    */
}
