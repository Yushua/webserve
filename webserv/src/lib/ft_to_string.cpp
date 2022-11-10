#include <ft_lib.hpp>
#include <string>

using namespace std;

const string ft_to_string(size_t n) {

	static char buffer[25];

	char *buffer_ptr = buffer + sizeof(buffer) - 1;
	*buffer_ptr = '\0';
	
	do { *--buffer_ptr = n % 10 + '0'; }
	while (n /= 10);

	return string(buffer_ptr);
}
