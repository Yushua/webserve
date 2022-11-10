#include <webserv.hpp>
#include <colors.hpp>
#include <string>
#include <iostream>

void webserv::config_set_body_size(string path, const string &size, int line) {
	
	Config_s *config = &default_config;
	if (path != "/") {
		map<string, struct Config_s>::iterator found = configs.find(path); 
		if (found != configs.end())
			config = &(found->second);
		else {
			std::cerr << RED << "  -~={ line " << line << ": No redirect from: " << path << " }=~-\n" << RESET;
			exit(1);
		}
	}
#ifdef DEBUG
	else
		path = "/";
#endif

	if (size == "") {
		std::cerr << RED << "  -~={ line " << line << ": Invalid file size format: " << size << " }=~-\n" << RESET;
		exit(1);
	}

	string actual_value;
	size_t mul_value = 1;
	
	if (size.length() < 3)
		actual_value = size;
	else {
		size_t split_index = size.length();
		string type = size.substr(split_index - 2, 2);
		if (type.find_first_not_of("0123456789") == string::npos) {
			actual_value = size;
		}
		else {
			actual_value = size.substr(0, split_index - 2);
			if (type == "kb" || type == "KB")
				mul_value = KILOBYTE;
			else if (type == "mb" || type == "MB")
				mul_value = MEGABYTE;
			else if (type == "gb" || type == "GB")
				mul_value = GIGABYTE;
			else {
				std::cerr << RED << "  -~={ Invalid file size format: " << type << " }=~-\n" << RESET;
				return;
			}
		}
	}
	if (actual_value.length() > 10) {
		std::cerr << RED << "  -~={ Number too long: " << actual_value << " }=~-\n" << RESET;
		return;
	}
	if (actual_value.find_first_not_of("0123456789") != string::npos) {
		std::cerr << RED << "  -~={ Invalid number: " << actual_value << " }=~-\n" << RESET;
		return;
	}

	config->client_body_size = atoi(actual_value.c_str()) * mul_value;
#ifdef DEBUG
	std::cout << GREEN << "  -~={ " << path << ": Body size set to " << size << " }=~-\n" << RESET;	
#endif
}
