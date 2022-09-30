#include <ft_lib.hpp>
#include <string>

using namespace std;

static char static_buffer[20] = "0000000000000000000";

const string ft_to_string(unsigned long n) {
	char *buffer_ptr = static_buffer + 19;
	
	while (n > 9) {
		*buffer_ptr = n % 10 + '0';
		n /= 10;
		--buffer_ptr;
	}
	*buffer_ptr = n % 10 + '0';
	n /= 10;

	return string(buffer_ptr);
}
