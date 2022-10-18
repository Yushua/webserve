/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   configParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 09:43:50 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/14 16:49:27 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <webserv.hpp>
// #include <message.hpp>

// //make own class
// #include <iostream>
// #include <fstream>
// #include <string>

// vector<std::string, std::string> configSplit(std::string string, char c)
// {
//     vector<std::string, std::string> vec;
//     int lenght = string.lenght();
//     for (int i = 0; i < lenght; i++)
//     {
//         if (string[i] == c)
//             break;
//     }
//     vec[0] = string.substr(0, i);
//     vec[1] = string.substr(i+1, lenght - 1 - i);
//     return(vec);
// }

// void configParser(map<string, webserv> &bigacontyantnas)
// {
//     std::ifstream infile("root/config/default.conf");
//     std::string line;
//     bool status = false;
//     vector<std::string, std::string> vec;
//     vector<std::string, std::string> _substring;
//     while (std::getline(infile, line)){
//         std::istringstream iss(line);
//         if (line.find("\t")  != string::npos && line.size() > 0){
//             //start new server
//             std::string name = line;
//         }
//         else{
//             line.replace("\t", "");
//             _substring = configSplit(line, " ");
//             if (_substring[0] == "cgi:"){
//                 vec = configSplit(_substring[1], '=');
//                 //check for path
//             }
//             else if (_substring[0] == "error_page:"){
//                 vec = configSplit(_substring[1], '=');
//                 //set error message
//             }
//             else if (_substring[0] == "listen:"){
//                 vec = configSplit(_substring[1], '=');
//                 //set port
//             }
//             else{
//                 while (std::getline(infile, line))
//                 {
//                     if (line.find("\t\t")  != string::npos){
//                         line.replace("\t", "");
//                         vec = configSplit(line, ": ");
//                         if (vec[0] == "method:"){
//                             if (vec[1].find("GET") != string::npos){
//                                 server.config_add_method(_substring[0], "GET");
//                             }
//                             else if (vec[1].find("HEAD") != string::npos){
//                                 server.config_add_method(_substring[0], "HEAD");
//                             }
//                             else if (vec[1].find("POST") != string::npos){
//                                 server.config_add_method(_substring[0], "POST");
//                             }
//                             else if (vec[1].find("DELETE") != string::npos){
//                                 server.config_add_method(_substring[0], "DELETE");
//                             }
//                         }
//                         else if (vec[0] == "dir_behavior:"){
//                             server.config_set_dir_behavior(_substring[0], vec[1]);
//                         }
//                         else if (vec[0] == "client_body_size:"){
//                             server.config_set_body_size(_substring[0], vec[1]);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }
