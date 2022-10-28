#include <webserv.hpp>
#include <colors.hpp>
#include <sstream>

const static char _page_start[] =
"<!DOCTYPE html>"
"<head>"
"<title>Index of /godotengine/4.0/beta1/mono/</title>"
"<style type=\"text/css\">"
"a, a:active {text-decoration: none; color: blue;}"
"a:visited {color: #48468F;}"
"a:hover, a:focus {text-decoration: underline; color: red;}"
"body {background-color: #F5F5F5;}"
"h2 {margin-bottom: 12px;}"
"table {margin-left: 12px;}"
"th, td { font: 90% monospace; text-align: left;}"
"th { font-weight: bold; padding-right: 14px; padding-bottom: 3px;}"
"td {padding-right: 14px;}"
"td.s, th.s {text-align: right;}"
"div.list {"
	"background-color: white;"
	"border-top: 1px solid #646464;"
	"border-bottom: 1px solid #646464;"
	"border-left: 1px solid #646464;"
	"border-right: 1px solid #646464;"
	"padding-top: 10px;"
	"padding-bottom: 14px;"
"}"
"div.foot { font: 90% monospace; color: #787878; padding-top: 4px;}"
"</style>"
"</head>"
"<body>";

const static char _table_start[] =
"<div class=\"list\">"
"<table summary=\"Directory Listing\" cellpadding=\"0\" cellspacing=\"0\">"
"<thead><tr><th class=\"n\">Name</th><th class=\"m\">Last Modified</th><th class=\"s\">Size</th></tr></thead>"
"<tbody>";

const static char _page_end[] =
"</tbody>"
"</table>"
"</div>"
"</body>"
"</html>";


int webserv::generate_index_page(const int index, const message &msg) {

	(void)index;
	const string &path = msg.getPath();
	string dir_path = msg.getStartLine().at(1);
	if (dir_path == "/")
		dir_path.clear();

	ostringstream page_stream;

	page_stream << _page_start;

	page_stream << "<h2>Index of " << dir_path << "/</h2>";

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
			<< "<tr>"
			<< "<td class=\"n\"><a href=\""
				<< dir_path << '/' << dir->d_name << "\">"
				<< dir->d_name << "</a>"
				<< (S_ISDIR(file_info.st_mode)?"/":"") << "</td>"
			<< "<td class=\"m\">"
				<< ctime(&file_info.st_mtime) << "</a></td>"
			<< "<td class=\"s\">"
				<< file_info.st_size << "</a></td>"
			<< "</tr>";
	}
	closedir(d);

	page_stream << _page_end;

	int fds[2];
	if (pipe(fds) != 0)
		ft_error("generate_index_page");



	string page = page_stream.str();
	write(fds[1], page.c_str(), page.length());
	close(fds[1]);

	fcntl(fds[0], O_NONBLOCK);
	return fds[0];
}
