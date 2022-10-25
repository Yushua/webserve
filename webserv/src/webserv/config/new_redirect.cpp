#include <webserv.hpp>
#include <colors.hpp>
#include <string>
#include <iostream>

void webserv::config_new_redirect(string path, string redirect_path, int line) {
	
	struct stat file_info;
	if (stat(redirect_path.c_str(), &file_info) == -1) {
		std::cerr << RED << "  -~={ line " << line << ": Redirect: path " << redirect_path << " doesn't exist }=~-\n" << RESET;
		exit(1);
	}
	if (!S_ISDIR(file_info.st_mode)) {
		std::cerr << RED << "  -~={ line " << line << ": error_page: " << redirect_path << " is not a directory }=~-\n" << RESET;
		exit(1);
	}

	if (path == "/") {
		default_config.redirect_path = redirect_path;
		default_config.allowed_methods.clear();
		default_config.dir_behavior = "list";
		default_config.client_body_size = 0;
	}
	else {
		map<string, struct Config_s>::iterator found = configs.find(path); 
		if (found != configs.end()) {
			std::cerr << RED << "  -~={ line " << line << ": Redirect already present: " << path << " }=~-\n" << RESET;
			exit(1);
		}

		struct Config_s conf;
		conf.redirect_path = redirect_path;
		conf.allowed_methods.clear();
		conf.dir_behavior = "list";
		conf.client_body_size = 0;
		configs.insert(pair<string, struct Config_s>(path, conf));
	}


#ifdef DEBUG
	std::cout << GREEN << "  -~={ New redirect: " << path << " >> " << redirect_path << " }=~-\n" << RESET;	
#endif
}
