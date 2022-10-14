#include <webserv.hpp>
#include <colors.hpp>
#include <string>
#include <iostream>

void webserv::config_set_dir_behavior(string path, const string &behavior) {
	
	Config_s *config = &default_config;
	if (path != "/") {
		map<string, struct Config_s>::iterator found = configs.find(path); 
		if (found != configs.end())
			config = &(found->second);
		else {
			std::cerr << RED << "  -~={ No redirect from: " << path << " }=~-\n" << RESET;
			return;
		}
	}
#ifdef DEBUG
	else
		path = "/";
#endif

	if (behavior != "list" && behavior != "error") {
		struct stat file_info;	
		if (stat(behavior.c_str(), &file_info) == -1) {
			std::cerr << RED << "  -~={ dir_behavior: path " << behavior << " doesn't exist }=~-\n" << RESET;
			return;
		}
		if (!S_ISREG(file_info.st_mode)) {
			std::cerr << RED << "  -~={ dir_behavior: " << behavior << " is not a file }=~-\n" << RESET;
			return;
		}
	}

	config->dir_behavior = behavior;

#ifdef DEBUG
	std::cout << GREEN << "  -~={ " << path << ": Set dir behavior to " << behavior << " }=~-\n" << RESET;	
#endif
}
