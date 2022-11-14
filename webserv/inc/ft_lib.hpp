#ifndef FT_LIB_HPP
	#define FT_LIB_HPP

#include <string>
#include <cstdlib>

/* error */
int ft_error(const char *str);

/* string and path */
const std::string ft_to_string(const size_t n);
const std::string ft_get_extension(const std::string &path);
std::vector<std::string> splitStringByString(std::string string, const char *str);
std::string &ft_to_lower(std::string &str);

#endif
