#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int ft_error(const char *str)
{
	perror(str);
	exit(1);
	return 0;
}

int ft_error(std::string *str)
	{ return ft_error(str->c_str()); }

int ft_error(std::string &str)
	{ return ft_error(str.c_str()); }
