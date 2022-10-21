#include <webserv.hpp>
#include <colors.hpp>

void webserv::config_add_error_page(const unsigned int error, const string page_path) {
	
	map<int, string>::iterator found = error_pages.find(error);
	if (found != error_pages.end()) {
		std::cerr << RED << "  -~={ error_page #" << error << " already exists }=~-\n" << RESET;
		return;
	}
	
	if (error < 400 || error >= 600) {
		std::cerr << RED << "  -~={ error_page: " << error << " is invalid }=~-\n" << RESET;
		return;
	}
	
	struct stat file_info;
	if (stat(page_path.c_str(), &file_info) == -1) {
		std::cerr << RED << "  -~={ error_page: path " << page_path << " doesn't exist }=~-\n" << RESET;
		return;
	}
	if (!S_ISREG(file_info.st_mode)) {
		std::cerr << RED << "  -~={ error_page: " << page_path << " is not a file }=~-\n" << RESET;
		return;
	}
	error_pages.insert(pair<int, string>(error, page_path));
#ifdef DEBUG
	std::cout << GREEN << "  -~={ Added new page for error #" << error << " }=~-\n" << RESET;	
#endif
}

void webserv::config_add_error_page(const string error, const string page_path) {
	if (error.find_first_not_of("0123456789") != string::npos) {
		std::cerr << RED << "  -~={ Invalid error_page number " << error << " }=~-\n" << RESET;
		return;
	}
	config_add_error_page(atoi(error.c_str()), page_path);
}
