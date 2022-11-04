#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/stat.h>

using namespace std;

int main(int argc, char**argv, char**envp) {
	(void)argc;
	(void)argv;
	
	cerr << "CGI START\n";
	
	ofstream file;
	string line;

	mkdir("uploads", 0777);

	getline(cin, line);
	cerr << line << '\n';
	string filename
		= line.substr(line.find("filename=\"") + 10);
	filename.erase(filename.length() - 2);
	cerr << filename << '\n';
	getline(cin, line);
	getline(cin, line);

	file.open("uploads/" + filename);
	while (getline(cin, line)) {
		file << line << '\n';
	}
	file.close();

	cerr << "CGI END\n";
}
