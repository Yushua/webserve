/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   configParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 09:43:50 by ybakker       #+#    #+#                 */
/*   Updated: 2022/11/02 17:27:29 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>
#include <message.hpp>

//make own class
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <colors.hpp>
vector<std::string> configSplit(std::string string, const char *str)
{
    vector<std::string> vec;
    int length = string.length();
    int subl = strlen(str);
    int i = 0;
    bool value = true;

    /*
    checks if the sequence,
    when the string[i] equals the first character in the sequence
    then it will go through, if somewhere it fails, then it stops.
    only when all of them compare, does it elave the false bool
    and leaves the while.
    */
    while (i < length && value == true)
    {
        if (string[i] == str[0]){
            for (int y = 0; str[y] && value == true; y++){
                if (string[i] == str[y])
                    value = false;
                else{
                    value = true;
                    break;
                }
            }
        }
        i++;
    }
    vec.push_back(string.substr(0, i - 1));
    if (static_cast<unsigned long>(i + 1) == string.length())
        vec.push_back("");
    else
        vec.push_back(string.substr(i + subl - 1, length - subl - i + 1));
    return(vec);
}

static int path_check(std::string path){
    ifstream myfile;
    myfile.open(path);
    if (!myfile){
        myfile.close();
        return -1;
    }return 0;
}

void configParser(map<string, webserv*> &bigacontyantnas, std::string path_config)
{
    if (path_check(path_config) == -1){
        std::cout << "invalid config file path\n";
        exit(1);
    }
    std::ifstream infile(path_config);//root/config/default.conf

    std::string line;//stores the line I am checking frm the config file
    vector<std::string> vec;//store the split line
    vector<std::string> _substring;//store the split line before in case it is needed
    vector<std::string> _reDirect;//store the split line before in case it is needed
    std::string webservName;
    int status = 0;
    /*
    -1: the start of the server creation
    0 : name created, now looking for whats next
    */
    bool reDirect = false;
    for (int i = 1; std::getline(infile, line); i++){
        if (line.find_first_not_of("\n\t ") == string::npos)
            {continue;}
        else if ((status == 0 || status == 1) && line.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-123456789") == string::npos){
            _reDirect.clear();
            _reDirect.push_back("/");
            _reDirect.push_back("root");
            webservName = line;
            bigacontyantnas.insert(std::pair<string, webserv*>(webservName, new webserv()));
            status = 1;
            std::cout << "\nservername==[" << line << "]" << std::endl;
            reDirect = false;
        }
        else if (line.find(": ") == string::npos || line.length() < 2){

            std::cerr << RED << "  -~={ 1 Invalid syntax on line: " << i << " }=~-\n" << RESET;
            exit(1);
        }
        else if (status == 1){
            while (line[0] == '\t' || line[0] == ' ' ){
                line.replace(0, 1, "");
            }
            vec = configSplit(line, ": ");
            if(line[0] == '/'){//syntax
                _reDirect = vec;
                // std::cout << "adding normal syntax[" << _reDirect[0] << "]\n";
                bigacontyantnas.at(webservName)->config_new_redirect(_reDirect[0], _reDirect[1], i);
                reDirect = true;
            }
            else if ((vec[0] == "method" || vec[0] == "client_body_size" || vec[0] == "dir_behavior") && reDirect == false){
                // std::cout << "adding default syntax [" << _reDirect[0] << "]\n";
                // std::cout << "name of server " << webservName << std::endl;
                bigacontyantnas.at(webservName)->config_new_redirect(_reDirect[0], _reDirect[1], i);
                reDirect = true;
            }
            //check if everythign is there
            if (vec[0] == "method"){
                std::string full = vec[1];
                std::string tmp;
                // std::cout << "name of server " << webservName << std::endl;
                if (full.length() > 0){
                    while (full.find(" ") != string::npos){
                        tmp = full.substr(0, full.find(" "));
                        full.erase(0, full.find(" ") + 1);
                        bigacontyantnas.at(webservName)->config_add_method(_reDirect[0], tmp, i);
                    }
                    bigacontyantnas.at(webservName)->config_add_method(_reDirect[0], full, i);
                }
            }
            else if (vec[0] == "client_body_size"){
                bigacontyantnas.at(webservName)->config_set_body_size(_reDirect[0], vec[1], i);
            }
            else if (vec[0] == "dir_behavior"){
                bigacontyantnas.at(webservName)->config_set_dir_behavior(_reDirect[0], vec[1], i);
            }
            else if (vec[0] == "listen"){
                bigacontyantnas.at(webservName)->config_listen_to_port(vec[1], i);
            }
            else if (vec[0] == "cgi"){
                _substring = configSplit(vec[1], "=");//kk
                bigacontyantnas.at(webservName)->config_add_cgi_option(_substring[0], _substring[1], i);
            }
            else if (vec[0] == "error_page"){
                _substring = configSplit(vec[1], "=");
                bigacontyantnas.at(webservName)->config_add_error_page(_substring[0], _substring[1], i);
            }
            else if (reDirect == true){
                continue;
            }
            else{
                // std::cerr << YELLOW << "[" << line << RESET << "]" << std::endl;
                std::cerr << RED << "  -~={ Invalid syntax on line: " << i << " }=~-\n" << RESET;
                exit(1);
            }
        }
    }
}
