/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   configParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 09:43:50 by ybakker       #+#    #+#                 */
/*   Updated: 2022/10/24 17:15:41 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>
#include <message.hpp>

//make own class
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

static vector<std::string> configSplit(std::string string, const char *str)
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

// static void throwError(std::string string, int i){
//     std::cout << "-~={ line [" << i << "] in parser is wrong with input [" << string << "] }=~-\n";
// }

void configParser(map<string, webserv*> &bigacontyantnas)
{
    std::ifstream infile("root/config/default.conf");
    std::string line;//stores the line I am checking frm the config file
    vector<std::string> vec;//store the split line
    vector<std::string> _substring;//store the split line before in case it is needed
    vector<std::string> _reDirect;//store the split line before in case it is needed
    std::string webservName;
    int status = -1;
    int i = 0;
    /*
    -1: the start of the server creation
    0 : name created, now looking for whats next
    1 : in the listen parser
    2 : in the syntax parser*/
    _reDirect.push_back("/:");
    _reDirect.push_back("root");
    bool reDirect = false;
    while (std::getline(infile, line)){
        if (status == -1){
            if (line == "" || line[0] == '\t' || line[0] == '\n' || line[0] == ' '){//if looking for name,  but there is only this
                i++;
            }
            else{//name found, because there is somethign to put in as a name
                webservName = line;
                bigacontyantnas.insert(std::pair<string, webserv*>(webservName, new webserv()));
                status = 0;
                std::cout << "name [" << webservName << "]\n";
            }
        }
        else if (status == 0 && line.length() > 2 && line.find(": ")){
            while (line[0] == '\t' ||line[0] == ' ' ){
                line.replace(0, 1, "");
            }
            vec = configSplit(line, ": ");
            if(line[0] == '/'){//syntax
                _reDirect = vec;
                bigacontyantnas.at(webservName)->config_new_redirect(_reDirect[0], _reDirect[1]);
                reDirect = true;
            }
            //if there is no syntax, why the error
            else if ((vec[0] == "method" || vec[0] == "client_body_size" || vec[0] == "dir_behavior") && reDirect == false){
                bigacontyantnas.at(webservName)->config_new_redirect(_reDirect[0], _reDirect[1]);
            }
            if (vec[0] == "method"){
                std::string full = vec[1];
                std::string tmp;
                //check if nothing is in there
                if (full.length() > 0){
                    while (full.find(" ") != string::npos){
                        tmp = full.substr(0, full.find(" "));
                        full.erase(0, full.find(" ") + 1);
                        bigacontyantnas.at(webservName)->config_add_method(_reDirect[0], tmp);
                    }
                    bigacontyantnas.at(webservName)->config_add_method(_reDirect[0], full);
                }
            }
            else if (vec[0] == "client_body_size"){
                bigacontyantnas.at(webservName)->config_set_body_size(_reDirect[0], vec[1]);
            }
            else if (vec[0] == "dir_behavior"){
                bigacontyantnas.at(webservName)->config_set_dir_behavior(_reDirect[0], vec[1]);
            }
            else if (vec[0] == "client_body_size"){
                bigacontyantnas.at(webservName)->config_set_body_size(_reDirect[0], vec[1]);
            }
            else if (vec[0] == "listen"){bigacontyantnas.at(webservName)->config_listen_to_port(vec[1]);}
            else if (vec[0] == "cgi"){
                _substring = configSplit(vec[1], "=");//kk
                bigacontyantnas.at(webservName)->config_add_cgi_option(_substring[0], _substring[1]);
            }
            else if (vec[0] == "error_page"){
                _substring = configSplit(vec[1], "=");
                bigacontyantnas.at(webservName)->config_add_error_page(_substring[0], _substring[1]);
            }
            else if (line.find_first_not_of("\n\t ") != string::npos)
                {continue;}
            else
                {status = -1;}
        }
        i++;
    }
}
