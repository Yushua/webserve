#include <ft_lib.hpp>
#include <string>

using namespace std;

#define BUFFER_SIZE 25
static char static_buffer[BUFFER_SIZE];

const string ft_to_string(size_t n) {
	static_buffer[BUFFER_SIZE - 1] = '\0';
	char *buffer_ptr = static_buffer + BUFFER_SIZE - 2;
	
	while (n > 9) {
		*buffer_ptr = n % 10 + '0';
		n /= 10;
		--buffer_ptr;
	}
	*buffer_ptr = n % 10 + '0';
	n /= 10;

	return string(buffer_ptr);
}
