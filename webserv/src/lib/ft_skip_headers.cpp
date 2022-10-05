#include <string>

using namespace std;

const string ft_skip_heders(const string &str) {
	int nl_count = 0;
	size_t len = str.length();

	for (size_t i = 0; i < len; ++i) {
		if (str[i] == '\n')
			nl_count++;
		else
			nl_count = 0;
		if (nl_count == 2)
			return str.substr(i + 1, len - i - 1);
	}

	return str;
}
