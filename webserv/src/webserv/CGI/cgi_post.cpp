#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//check fi this body is chunked

void webserv::cgi_post(std::string string, const int index, message &msg) {

	std::string boundary = "--" + string;
	std::cout << "hey[" << boundary  << "]" << std::endl;

	std::string path = msg.getBody();
	int i = 0;

	i = index;
	// std::cout << YELLOW << path << RESET << std::endl;
	// int end = 0;
	std::ifstream infile("root/cgo-bin/cgi-test.txt");
	std::string line;
	// while (end == 0){
	// 	if (std::getline(infile, line) == boundary)
	// }
	return ;
}
