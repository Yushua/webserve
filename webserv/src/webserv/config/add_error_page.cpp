#include <webserv.hpp>
#include <colors.hpp>

void webserv::config_add_error_page(const unsigned error, const string page_path) {
	if (error < 400 || error >= 600) {
		std::cerr << RED << "  -~={ error_page: " << error << " is invalid }=~-\n" << RESET;
	}
	
	struct stat file_info;
	if (stat(page_path.c_str(), &file_info) == -1) {
		std::cerr << RED << "  -~={ error_page: " << page_path << " doesn't exist }=~-\n" << RESET;
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
	config_add_error_page(atoi(error.c_str()), page_path);
}

// https://linux.die.net/man/2/stat
