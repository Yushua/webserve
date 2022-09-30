#ifndef FT_LIB_HPP
	#define FT_LIB_HPP

#include <string>

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

/* ft_error.cpp */
int ft_error(const char *str);
int ft_error(std::string *str);
int ft_error(std::string &str);

/* ft_to_string.cpp */
const std::string ft_to_string(const ulong n);

#endif
