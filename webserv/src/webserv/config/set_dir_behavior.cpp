#include <webserv.hpp>
#include <colors.hpp>
#include <string>
#include <iostream>

void webserv::config_set_dir_behavior(string path, const string &behavior, int line) {
	
	Config_s *config = &default_config;
	if (path != "/") {
		map<string, struct Config_s>::iterator found = configs.find(path); 
		if (found != configs.end())
			config = &(found->second);
		else {
			std::cerr << RED << "  -~={ line " << line << ": No redirect from: " << path << " }=~-" << RESET << '\n';
			exit(1);
		}
	}
#ifdef DEBUG
	else
		path = "/";
#endif

	if (behavior != "list" && behavior != "error") {
		struct stat file_info;	
		if (stat(behavior.c_str(), &file_info) == -1) {
			std::cerr << RED << "  -~={ line " << line << ": dir_behavior: path " << behavior << " doesn't exist }=~-" << RESET << '\n';
			exit(1);
		}
		if (!S_ISREG(file_info.st_mode)) {
			std::cerr << RED << "  -~={ line " << line << ": dir_behavior: " << behavior << " is not a file }=~-" << RESET << '\n';
			exit(1);
		}
	}

	config->dir_behavior = behavior;

#ifdef DEBUG
	std::cout << GREEN << "  -~={ " << path << ": Set dir behavior to " << behavior << " }=~-" << RESET << '\n';	
#endif
}
