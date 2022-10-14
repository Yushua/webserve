#ifndef CONFIG_STRUCT_HPP
	#define CONFIG_STRUCT_HPP

#include <string>
#include <vector>

struct Config_s {
	std::string redirect_path; //
	std::vector<std::string> allowed_methods; // method:
	size_t client_body_size; // client_body_size:
	std::string dir_behavior; // dir_behavior:
};

#endif
