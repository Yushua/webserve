#include <webserv.hpp>
#include <colors.hpp>
#include <fstream>

void webserv::config_add_cgi_option(const string extension, const string interpreter_path) {
	if (interpreter_path != "") {
		struct stat file_info;	
		if (stat(interpreter_path.c_str(), &file_info) == -1) {
			std::cerr << RED << "  -~={ cgi: " << interpreter_path << " doesn't exist }=~-\n" << RESET;
			return;
		}
		if (!S_ISREG(file_info.st_mode)) {
			std::cerr << RED << "  -~={ cgi: " << interpreter_path << " is not a file }=~-\n" << RESET;
			return;
		}
	}
	cgi_options.insert(pair<string, string>(extension, interpreter_path));
#ifdef DEBUG
	std::cout << GREEN << "  -~={ New cgi option for ." << extension << " }=~-\n" << RESET;
#endif
}
