#include <webserv.hpp>

const string webserv::header_get_content_type(const string filename) {
	string extension = ft_get_extension(filename);

	if (extension == "html")
		return "Content-type: text/html\n";
	if (extension == "txt")
		return "Content-type: text/plain\n";

	if (extension == "jpg" || extension == "jpeg")
		return "Content-type: image/jpeg\n";
	if (extension == "png")
		return "Content-type: image/png\n";
	if (extension == "gif")
		return "Content-type: image/gif\n";
	if (extension == "ico")
		return "Content-type: image/vnd.microsoft.icon\n";
	return "";
}