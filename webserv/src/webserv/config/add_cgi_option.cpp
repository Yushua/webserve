#include <webserv.hpp>
#include <colors.hpp>
#include <fstream>

void webserv::config_add_cgi_option(string extension, string interpreter_path) {
	(void)extension;
	ifstream file(interpreter_path);
	if (!file.good()) {
		std::cerr << RED << "  -~={ cgi: no file at " << interpreter_path << " }=~-\n" << RESET;
		return;
	}
	file.close();
	cgi_options.insert(pair<string, string>(extension, interpreter_path));
#ifdef DEBUG
	std::cout << GREEN << "  -~={ New cgi option for ." << extension << " }=~-\n" << RESET;
#endif
}
