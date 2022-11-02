#include <message.hpp>
#include <webserv.hpp>

void message::redirect(webserv &server) {
	map<string, struct Config_s>::iterator itr = server.configs.begin();
	map<string, struct Config_s>::iterator end = server.configs.end();

	struct Config_s *found_conf = &(server.default_config);
	const string *redirect_from;	
	for (; itr != end; ++itr) {
		redirect_from = &(itr->first);
		if (strncmp(redirect_from->c_str(), path.c_str(), redirect_from->length()) == 0)
			{ found_conf = &(itr->second); break; }
	}

	config = *found_conf;

	if (strncmp(config.redirect_path.c_str(), ">> ", 3) == 0) {
		stat_state = false;
		actualPath = config.redirect_path + path;
		this->reset();
		return;
	}

	if (found_conf == &(server.default_config))
		actualPath = config.redirect_path + path;
	else {
		actualPath = config.redirect_path + path.substr(redirect_from->length(), path.length() - redirect_from->length());
	}



	struct stat file_info;	
	if (stat(actualPath.c_str(), &file_info) == -1)
		stat_state = false;
	else {
		stat_state = true;
		stat_result = file_info;
	}
}
