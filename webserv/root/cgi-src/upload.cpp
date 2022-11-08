#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/stat.h>

using namespace std;

int main() {
	
	ofstream file;
	ofstream file2;
	string line;

	mkdir("root/uploads", 0777);

	getline(cin, line);
	string filename
		= line.substr(line.find("filename=\"") + 10);
	filename.erase(filename.length() - 2);
	getline(cin, line);
	getline(cin, line);

	file.open("root/uploads/" + filename);
	while (getline(cin, line))
		file << line << '\n';
	file.close();

	cout <<
		"HTTP/1.1 200\n\n"
		"<!DOCTYPE html>"
		"<html>"
		"<body>"
		"<h1>This is the uploading CGI!</h1>"
		"The file(s) can be found <a href=\"/uploads\">here</a>,"
		" unless the server says otherwise."
		"</body>"
		"</html>"
		;
}
