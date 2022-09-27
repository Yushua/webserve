#ifndef ERROR_HPP
	#define ERROR_HPP

#include <string>

/* error.cpp */
int error(const char *str);
int error(std::string *str);
int error(std::string &str);

#endif
