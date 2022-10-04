#include <ft_lib.hpp>
#include <string>

using namespace std;

static char static_buffer[20];

const string ft_to_string(unsigned long n) {
	static_buffer[19] = '\0';
	char *buffer_ptr = static_buffer + 18;
	
	while (n > 9) {
		*buffer_ptr = n % 10 + '0';
		n /= 10;
		--buffer_ptr;
	}
	*buffer_ptr = n % 10 + '0';
	n /= 10;

	return string(buffer_ptr);
}
