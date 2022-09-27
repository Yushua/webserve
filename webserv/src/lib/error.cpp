#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int error(const char *str)
{
	perror(str);
	exit(1);
	return 0;
}

int error(std::string *str)
	{ return error(str->c_str()); }

int error(std::string &str)
	{ return error(str.c_str()); }
