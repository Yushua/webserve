/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   configParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 09:43:50 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/20 16:35:01 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>
#include <message.hpp>

//make own class
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

static vector<std::string> configSplit(std::string string, const char *c)
{
    vector<std::string> vec;
    int length = string.length();
    int i = 0;
    while (i < length)
    {
        if (string[i] == c[0] && string[i+1] == c[1])
            break;
        i++;
    }
    vec.push_back(string.substr(0, i));
    vec.push_back(string.substr(i+2, length - 1 - i));
    return(vec);
}

static vector<std::string> configSplit(std::string string, const char c)
{
    vector<std::string> vec;
    int length = string.length();
    int i = 0;
    while (i < length)
    {
        if (string[i] == c)
            break;
        i++;
    }
    vec.push_back(string.substr(0, i + 1));
    if (static_cast<unsigned long>(i + 1) == string.length())
        vec.push_back("");
    else
        vec.push_back(string.substr(i+1, length - 1 - i));
    return(vec);
}

void configParser(map<string, webserv*> &bigacontyantnas)
{
    std::ifstream infile("root/config/default.conf");
    std::string line;
    bool status = false;
    vector<std::string> vec;
    vector<std::string> _substring;
    std::cout << "start" << std::endl;
    std::string webservName;
    while (std::getline(infile, line)){
        if (line[0] != '\t' && line.size() > 0){
            //start new server
            std::string name = line;
            webservName = line;
            std::cout << "======NAME IS HERE=====" << std::endl;
            bigacontyantnas.insert(std::pair<string, webserv*>(webservName, new webserv()));
        }
        else if (status == true) {
            if (line == "")
                status = false;
            else{
                while (line[0] == '\t')
                    line.replace(0, 1, "");
                vec = configSplit(line, ": ");
                if (vec[0] == "method:"){
                    std::string full = vec[1];
                    std::string tmp;
                    while (full.find(" ") != string::npos){
                        tmp = full.substr(0, full.find(" "));
                        full.erase(0, full.find(" ") + 1);
                        bigacontyantnas.at(webservName)->config_add_method(_substring[0], tmp);
                    }
                    bigacontyantnas.at(webservName)->config_add_method(_substring[0], full);
                }
                else if (vec[0] == "client_body_size:")
                    bigacontyantnas.at(webservName)->config_set_body_size(_substring[0], vec[1]);
                else if (vec[0] == "dir_behavior:")
                    bigacontyantnas.at(webservName)->config_set_dir_behavior(_substring[0], vec[1]);
            }
        }
        else if (line != "" && status == false){
            line.replace(0, 1, "");
            vec = configSplit(line, ": ");
            if (vec[0] == "listen"){
                std::cout << "=====Listen=====" << std::endl;
                bigacontyantnas.at(webservName)->config_listen_to_port(vec[1]);
            }
            else if (vec[0] == "cgi"){
                _substring = configSplit(vec[1], '=');
                std::cout << "=====CGI=====" << std::endl;
                bigacontyantnas.at(webservName)->config_add_cgi_option(_substring[0], _substring[1]);
            }
            else if (vec[0] == "error_page"){
                _substring = configSplit(vec[1], '=');
                std::cout << "=====errorn=====" << std::endl;
                bigacontyantnas.at(webservName)->config_add_error_page(_substring[0], _substring[1]);
            }
            else{
                status = true;
                _substring = vec;
                bigacontyantnas.at(webservName)->config_new_redirect(_substring[0], _substring[1]);
            }
        }
    }
}
