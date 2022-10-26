#ifndef FT_LIB_HPP
	#define FT_LIB_HPP

#include <string>
#include <cstdlib>

/* error */
int ft_error(const char *str);
int ft_error(std::string *str);
int ft_error(std::string &str);

/* string and path */
const std::string ft_to_string(const size_t n);
const std::string ft_substr(const std::string &str, size_t start, size_t len);
const std::string ft_fd_to_str(const int fd);
const std::string ft_get_extension(const std::string &path);
const std::string ft_skip_heders(const std::string &str);
vector<std::string> configSplit(std::string string, const char *str);

#endif
