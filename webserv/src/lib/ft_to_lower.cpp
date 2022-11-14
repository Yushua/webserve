#include <string>
#include <algorithm>

using namespace std;

static char ascii_to_lower(char c) {
    return (c >= 'A' && c <= 'Z')
        ? c - ('Z' - 'z')
        : c;
}

string &ft_to_lower(string &str) {
	transform(str.begin(), str.end(), str.begin(), ascii_to_lower);
	return str;
}
