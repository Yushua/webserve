/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unChunk.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 20:17:59 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/14 16:49:50 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>

//each msg has their own bool NOW
#include <iostream>
#include <string>
#include <ctype.h>
#include <fcntl.h>

void message::unChunk(std::string _string)
{
    /*
        Transfer-Encoding: chunked
        Transfer-Encoding: compress
        Transfer-Encoding: deflate
        Transfer-Encoding: gzip

{
    
}
    */
    this->chunkS = true;
    static std::string chunk;
    if (!_string.find(" chunk")){
        this->chunkE = true;
    }
    bool status = false;
    status = true;
}
