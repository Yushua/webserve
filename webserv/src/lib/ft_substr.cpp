#include <ft_lib.hpp>
#include <string>
#include <iostream>

using namespace std;

const string ft_substr(const string &str, size_t start, size_t len) {
	if (start + len > str.length())
		cout << "\n\n{" << start << '+' << len << '=' << start + len << '>' << str.length()
			<< "}\n String {\n" << str << "\n} End of string\n\n";
	return str.substr(start, len);
}
