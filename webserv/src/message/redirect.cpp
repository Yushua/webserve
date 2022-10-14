#include <message.hpp>
#include <webserv.hpp>

void message::redirect(webserv &server) {
	map<string, struct Config_s>::iterator itr = server.configs.begin();
	map<string, struct Config_s>::iterator end = server.configs.end();

	config = server.default_config;
	
	for (; itr != end; ++itr) {
		const string &redirect_from = itr->first;
		if (strncmp(redirect_from.c_str(), path.c_str(), redirect_from.length()) == 0) {
			config = itr->second;
			path = config.redirect_path + path.substr(redirect_from.length(), path.length() - redirect_from.length());
			cout << "1 " << path << '\n';
			goto found_redirect;
		}
	}
	path = config.redirect_path + path;
	cout << "2 " << path << '\n';
	found_redirect:

	struct stat file_info;	
	if (stat(path.c_str(), &file_info) == -1)
		stat_result = -1;
	else
		stat_result = file_info.st_mode;
}
