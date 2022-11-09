#include <string>

using namespace std;

const string ft_get_extension(const string &path) {
	for (int i = path.length() - 1; i > 0; --i) {
		if (path[i] == '.') {
			return path.substr(i + 1, path.length() - i);
		}
	}
	return "";
}
