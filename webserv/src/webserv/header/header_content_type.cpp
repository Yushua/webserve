#include <webserv.hpp>

const string webserv::header_get_content_type(const string filename) {
	string extension = ft_get_extension(filename);

	if (extension == "html")
		return "Content-Type: text/html\n";
	if (extension == "txt")
		return "Content-Type: text/plain\n";

	if (extension == "jpg" || extension == "jpeg")
		return "Content-Type: image/jpeg\n";
	if (extension == "png")
		return "Content-Type: image/png\n";
	if (extension == "gif")
		return "Content-Type: image/gif\n";
	if (extension == "ico")
		return "Content-Type: image/vnd.microsoft.icon\n";
	return "";
}
