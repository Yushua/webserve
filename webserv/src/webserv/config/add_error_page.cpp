#include <webserv.hpp>
#include <colors.hpp>

void webserv::config_add_error_page(const int error, const string page_path) {
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

// https://linux.die.net/man/2/stat
