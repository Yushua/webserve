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
void webserv::cgi_post(const int index, const message &msg, const string &requested_file, const string &interpreter, std::string boundary){
    //open the input pipes
	//information is send to the output files
	int input_pipe[2];
    if (pipe(input_pipe) != 0)
        ft_error("cgi_pot input");
    int output_pip[2];
    if (pipe(output_pip) != 0)
        ft_error("cgi_post output");
	int posa = 0;
	int posb = 0;
	std::string str = "";
	posa = posb + boundary.length() + 1;
	posb = msg.getBody().find(boundary, posa);
	// std::cout << RED << msg.getBody().substr(posa, posb) << RESET << std::endl;
	int tmp;
	tmp = index;
	std::string tmp1 = requested_file;
	std::string tmp2 = interpreter;
	// while (true){
		// int fork_res = fork();
		// if (fork_res == -1)
		// 	ft_error("fork");
		// /* Is not child */
		// if (fork_res != 0) {
		// 	close(output_pip[1]);
		// 	close(input_pipe[0]);
		// 	close(input_pipe[1]);
		// 	fcntl(output_pip[0], O_NONBLOCK);
		// 	this->send_new(index, "HTTP/1.1 200 OK\n", output_pip[0]);
		// 	sockets_info[index].disconnect_after_send = true;
		// 	return;
		// }
		// else {
		// 	const vector<string> &args = msg.getArguments();
		// 	const char *argv[3] = {
		// 		interpreter != ""
		// 			? interpreter.c_str()
		// 			: requested_file.c_str(),
		// 		requested_file.c_str(),
		// 		NULL};
		// 	const char *envp[1] = { NULL };
		// 	dup2(output_pip[1], 1);
		// 	dup2(input_pipe[0], 0);
		// 	// for (string arg in msg.getArguments()) {
		// 	// 	write(input_pipe[1], arg + '\n');
		// 	// }
		// 	write(input_pipe[1], str.c_str(), str.length());
		// 	cerr << execve(argv[0], (char * const *)argv, (char * const *)envp) << '\n';
		// 	exit(1);
		// }
	// }
}
