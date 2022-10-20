/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unChunk.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 20:17:59 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/20 15:29:05 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.hpp>

//each msg has their own bool NOW
// #include <string>
// #include <vector>
// #include <sstream>
// #include <cstdlib>

void message::unChunk()
{
//     /*
//         Transfer-Encoding: chunked
//     {
//         4\r\n
//         Wiki\r\n6\r\n
//         pedia \r\n   (data)
//         E\r\n
//         in \r\n
//         \r\n
//         chunks.\r\n  (data)
//         0\r\n        (final byte - 0)
//         \r\n         (end message)
//     }
//     */
//     std::stringstream test(this->body);
//     std::string segment;
//     std::vector<std::string> seglist;

//     while(std::getline(test, segment, '\n'))
//         segment += segment;
//     while(std::getline(test, segment, '\r'))
//         seglist.push_back(segment);
//     bool status = false;
//     int vecSize = seglist.size();
//     this->valid = true;
//     unsigned int size = 0;
//     for (int i = 0; i < vecSize && this->valid == true; i++)
//     {
//         if (status == false)
//         {
//             if (seglist[i].find_first_not_of("0123456789") != string::npos)
//                 this->valid = false;
//             else
//                 size = atoi(seglist[i].c_str());
//             if (size == 0)
//                 break;
//         }
//         else if (status == true)
//         {
//             if (seglist[i].size() != size)
//                 this->valid = false;
//         }
//     }
}
