#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//check if this body is chunked

#define IS_NOT_CHILD fork_res != 0

//look into how other people do it, it seems the original plan went wrong
//look into how cgi actually works with the input
//you cna input part by part, storing the entire message into one string, but how
//does POST CGI actually handle it?
//how does pipe nand fork work in this matter
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

	//loop must end when the last post message has been uploaded
	// while (end == 0){
	// 	if (std::getline(infile, line) == boundary)
	// }
	// while (true){
	// 	int fds[2];
	// 	if (pipe(fds) != 0)
	// 		ft_error("cgi_get");
		
	// 	int fork_res = fork();

	// 	if (fork_res == -1)
	// 		ft_error("fork");

	// 	if (IS_NOT_CHILD) {
	// 		return;
	// 	}
	// 	else {
	// 		//making argv

	// 		//making envp
		
	// 		//execve
	// 		exit(1);
	// 	}
	// }
	return ;
}
