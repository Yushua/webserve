#include <string>

using namespace std;

const string ft_get_extension(const string &path) {
	string extension;

	for (int i = path.length() - 1; i > 0; --i) {
		if (path[i] == '.') {
			extension = path.substr(i + 1, path.length() - i);
			goto found;
		}
	}
	extension = path;
	found:
	return extension;
}
