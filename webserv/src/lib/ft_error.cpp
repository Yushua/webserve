#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int ft_error(const char *str)
{
	perror(str);
	exit(1);
	return 0;
}
