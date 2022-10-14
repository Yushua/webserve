#include <webserv.hpp>
#include <colors.hpp>
#include <string>
#include <iostream>

void webserv::config_add_method(string path, const string &method) {
	
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

	config->allowed_methods.push_back(method);

#ifdef DEBUG
	std::cout << GREEN << "  -~={ " << path << ": Added method " << method << " }=~-\n" << RESET;	
#endif
}