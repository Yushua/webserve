#include <webserv.hpp>

const string webserv::header_get_content_type(const string filename) {
	string extension = "";

	for (int i = filename.length() - 1; i > 0; i++) {
		if (filename[i] == '.') {
			extension = (char *)filename.c_str() + i + 1;
			break;
		}
	}

	if (extension == "")
		return "";
	if (extension == "html")
		return "Content-type: text/html\n";
	if (extension == "jpg")
		return "Content-type: image/jpg\n";
	if (extension == "png")
		return "Content-type: image/png\n";
	return "";
}
