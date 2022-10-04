#ifndef FT_LIB_HPP
	#define FT_LIB_HPP

#include <string>

/* ft_error.cpp */
int ft_error(const char *str);
int ft_error(std::string *str);
int ft_error(std::string &str);

/* ft_to_string.cpp */
const std::string ft_to_string(const size_t n);

/* ft_substr.cpp */
const std::string ft_substr(const std::string &str, size_t start, size_t len);

#endif
