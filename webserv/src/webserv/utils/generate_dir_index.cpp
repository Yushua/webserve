#include <webserv.hpp>
#include <colors.hpp>
#include <sstream>

const static char _page_start[] =
"<!DOCTYPE html>\n"
"<head>\n"
"<title>Index of /godotengine/4.0/beta1/mono/</title>\n"
"<style type=\"text/css\">\n"
"a, a:active {text-decoration: none; color: blue;}\n"
"a:visited {color: #48468F;}\n"
"a:hover, a:focus {text-decoration: underline; color: red;}\n"
"body {background-color: #F5F5F5;}\n"
"h2 {margin-bottom: 12px;}\n"
"table {margin-left: 12px;}\n"
"th, td { font: 90% monospace; text-align: left;}\n"
"th { font-weight: bold; padding-right: 14px; padding-bottom: 3px;}\n"
"td {padding-right: 14px;}\n"
"td.s, th.s {text-align: right;}\n"
"div.list {\n"
	"background-color: white;\n"
	"border-top: 1px solid #646464;\n"
	"border-bottom: 1px solid #646464;\n"
	"border-left: 1px solid #646464;\n"
	"border-right: 1px solid #646464;\n"
	"padding-top: 10px;\n"
	"padding-bottom: 14px;\n"
"}\n"
"div.foot { font: 90% monospace; color: #787878; padding-top: 4px;}\n"
"</style>\n"
"</head>\n"
"<body>\n";

const static char _table_start[] =
"<div class=\"list\">\n"
"<table summary=\"Directory Listing\" cellpadding=\"0\" cellspacing=\"0\">\n"
"<thead><tr><th class=\"n\">Name</th><th class=\"m\">Last Modified</th><th class=\"s\">Size</th></tr></thead>\n"
"<tbody>\n";

const static char _page_end[] =
"\n</tbody>\n"
"</table>\n"
"</div>\n"
"</body>\n"
"</html>\n";

static string static_get_file_size(size_t size) {
	if (size > GIGABYTE)
		return ft_to_string(size / GIGABYTE) + "gb";
	else if (size > MEGABYTE)
		return ft_to_string(size / MEGABYTE) + "mb";
	else if (size > KILOBYTE)
		return ft_to_string(size / KILOBYTE) + "kb";
	else
		return ft_to_string(size);
}

int webserv::generate_index_page(const int index, const message &msg) {

	(void)index;
	const string &path = msg.getPath();
	string dir_path = msg.getStartLine().at(1);
	if (dir_path == "/")
		dir_path.clear();

	ostringstream page_stream;

	page_stream << _page_start;

	page_stream << "<h2>Index of " << dir_path << "/</h2>\n";

	page_stream << _table_start;


    struct dirent *dir;
    DIR *d = opendir(path.c_str());
    if (!d)
		ft_error("generate_index_page");

	dir = readdir(d);
	for (dir = readdir(d); dir; dir = readdir(d)) {
		
		if (dir->d_namlen > 1
			&& dir->d_name[0] == '.'
			&& strcmp("..", dir->d_name) != 0)
			continue;

		if (dir_path == "" && strcmp("..", dir->d_name) == 0)
			continue;

		struct stat file_info;	
		string actual_path = path + '/' + dir->d_name;
		if (stat(actual_path.c_str(), &file_info) == -1)
			ft_error("generate_index_page");

		page_stream
			<< "\n<tr>\n"
			<< "<td class=\"n\"><a href=\n    \""
				<< dir_path << '/' << dir->d_name << "\">"
				<< dir->d_name << "\n</a>"
				<< (S_ISDIR(file_info.st_mode)?"/":"") << "</td>\n"
			<< "<td class=\"m\">\n    "
				<< ctime(&file_info.st_mtime) << "</a></td>\n"
			<< "<td class=\"s\">\n    "
				<< (S_ISDIR(file_info.st_mode)?"-":static_get_file_size(file_info.st_size))
					<< "\n</a></td>\n"
			<< "</tr>\n";
	}
	closedir(d);

	page_stream << _page_end;

	int fds[2];
	if (pipe(fds) != 0)
		ft_error("generate_index_page");



	string page = page_stream.str();
	page = "Content-Length: " + ft_to_string(page.length()) + "\n\n" + page;
	
	write(fds[1], page.c_str(), page.length());
	close(fds[1]);

	fcntl(fds[0], O_NONBLOCK);
	return fds[0];
}
