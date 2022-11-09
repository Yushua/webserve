#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char **argv) {

	if (argc != 2) {
		if (argc == 1)
			std::cout << "no config file was passed\n";
		else
			std::cout << "the amounth of inputs: [" << argc << "] is not the right amount\n";
		exit(1);
	}
	
	map<std::string, webserv*> webservMap;
	configParser(webservMap, argv[1]);
	
	map<std::string, webserv*>::iterator it;
	while (true)
		for (it = webservMap.begin(); it != webservMap.end(); it++)
			it->second->run();
}
