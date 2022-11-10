#include <webserv.hpp>
#include <colors.hpp>
#include <fstream>

void webserv::config_add_cgi_option(const string extension, const string interpreter_path, int line) {
	
	map<string, string>::iterator found = cgi_options.find(extension);
	if (found != cgi_options.end()) {
		std::cerr << RED << "  -~={ line " << line << ": cgi for ." << extension << " already exists }=~-" << RESET << '\n';
		return;
	}
	
	if (interpreter_path != "") {
		struct stat file_info;	
		if (stat(interpreter_path.c_str(), &file_info) == -1) {
			std::cerr << RED << "  -~={ line " << line << ": cgi: path " << interpreter_path << " doesn't exist }=~-" << RESET << '\n';
			return;
		}
		if (!S_ISREG(file_info.st_mode)) {
			std::cerr << RED << "  -~={ line " << line << ": cgi: " << interpreter_path << " is not a file }=~-" << RESET << '\n';
			return;
		}
	}
	cgi_options.insert(pair<string, string>(extension, interpreter_path));
#ifdef DEBUG
	std::cout << GREEN << "  -~={ New cgi option for ." << extension << " }=~-" << RESET << '\n';
#endif
}
