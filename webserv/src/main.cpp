#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char **argv) {
	//loop
	if (argc == 1) {
		std::cout << "no config file was passed\n";
		return (0);
	}
	if (argc != 2) {
		std::cout << "the amounth of inputs: [" << argc << "] is not the right amounth\n";
	}
	map<std::string, webserv*> webservMap;
	configParser(webservMap, argv[1]);//normal name
	map<std::string, webserv*>::iterator it;

	while (true) {
		for (it = webservMap.begin(); it != webservMap.end(); it++)
		{
			it->second->run();
		}
	}
}
