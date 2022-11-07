#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//check if this body is chunked

#define IS_NOT_CHILD fork_res != 0

//CGI turns the body, or the part of the body between the boundries into CGI and let it run
//Through EXECVE
void webserv::cgi_post_nb(int *input_pipe, int *output_pip, std::string send, const int index, const message &msg, const string &requested_file, const string &interpreter){
	/* writing send to see if everythin went well */
	std::cout << RED << "[" << send << "]" << RESET << std::endl;
	int fork_res = fork();
	std::cout << YELLOW << msg.getBody() << RESET << std::endl;
	if (fork_res == -1)
		ft_error("fork");
	/* Is not child */
	if (fork_res != 0) {
		write(input_pipe[1]
		, send.c_str()
		, send.length());
		close(input_pipe[0]);
		close(input_pipe[1]);
		
		close(output_pip[1]);
		fcntl(output_pip[0], O_NONBLOCK);
		this->send_new(index, "HTTP/1.1 200 OK\n", output_pip[0]);//casuing the leak problem
		sockets_info[index].disconnect_after_send = true;
		return;
	}
	else {
		const vector<string> &args = msg.getArguments();
		const char *argv[3] = {
			interpreter != ""
				? interpreter.c_str()
				: requested_file.c_str(),
			requested_file.c_str(),
			NULL};
		const char *envp[1] = { NULL };
		dup2(output_pip[1], 1);
		dup2(input_pipe[0], 0);
		size_t len = args.size();
		for (size_t i = 0; i < len; ++i) {
			write(input_pipe[1], args[i].c_str(), args[i].length());
			write(input_pipe[1], "\n", 1);
		}
		close(input_pipe[1]);
		std::cerr << execve(argv[0], (char * const *)argv, (char * const *)envp) << '\n';
		exit(1);
	}
}

void webserv::cgi_post_string(std::string header, std::string Content_Type, const int index, const message &msg, const string &requested_file, const string &interpreter){
	ofstream file;
	if (!msg.getStatState())//need to check if this is a chunk file, meaning it exist because a chunk has been send there
	{
		//if its folder
		if (S_ISDIR(msg.getStat().st_mode)){
			this->send_new_error_fatal(index, 404);
			return;
		}
		//when it does not exist, create
		file.open(msg.getPath(), fstream::in | fstream::out | fstream::trunc);
		if (!file.good()){
			this->send_new_error_fatal(index, 404);
			return;
		}
		file.close();
	}

	std::cout <<"CGI start string\n";
	std::cout << YELLOW << header << Content_Type << "\n" << msg.getBody() << RESET << std::endl;
	int input_pipe[2];
    if (pipe(input_pipe) != 0)
        ft_error("cgi_pot input");
    int output_pip[2];
    if (pipe(output_pip) != 0)
        ft_error("cgi_post output");
	int fork_res = fork();
	if (fork_res == -1)
		ft_error("fork");
	if (fork_res != 0) {
		
		write(input_pipe[1], header.c_str(), header.length());
		write(input_pipe[1], Content_Type.c_str(), Content_Type.length());
		write(input_pipe[1], "\n", 1);
		write(input_pipe[1], msg.getBody().c_str(), msg.getBody().length());

		close(input_pipe[0]);
		close(input_pipe[1]);
		
		close(output_pip[1]);
		fcntl(output_pip[0], O_NONBLOCK);
		this->send_new(index, "HTTP/1.1 200 OK\n", output_pip[0]);//casusing the leak problem
		sockets_info[index].disconnect_after_send = true;
		return;
	}
	else {
		const vector<string> &args = msg.getArguments();
		const char *argv[3] = {
			interpreter != ""
				? interpreter.c_str()
				: requested_file.c_str(),
			requested_file.c_str(),
			NULL};
		const char *envp[1] = { NULL };
		dup2(output_pip[1], 1);
		dup2(input_pipe[0], 0);
		size_t len = args.size();
		for (size_t i = 0; i < len; ++i) {
			write(input_pipe[1], args[i].c_str(), args[i].length());
			write(input_pipe[1], "\n", 1);
		}
		close(input_pipe[1]);
		std::cerr << execve(argv[0], (char * const *)argv, (char * const *)envp) << '\n';
		exit(1);
	}
}

void webserv::cgi_post(const int index, const message &msg, const std::string &requested_file, const std::string &interpreter, std::string boundary){
    //open the input pipes
	//information is send to the output files
	std::cout <<"CGI start\n";
	int input_pipe[2];
    if (pipe(input_pipe) != 0)
        ft_error("cgi_pot input");
    int output_pip[2];
    if (pipe(output_pip) != 0)
        ft_error("cgi_post output");
	boundary = "--" + boundary;
	int posa = 0;
	int posb = 0;
	std::string str = "";
	bool loop = true;
	ofstream file;
	if (!msg.getStatState())//need to check if this is a chunk file, meaning it exist because a chunk has been send there
	{
		//if its folder
		if (S_ISDIR(msg.getStat().st_mode)){
			this->send_new_error_fatal(index, 404);
			return;
		}
		//when it does not exist, create
		file.open(msg.getPath(), fstream::in | fstream::out | fstream::trunc);
		if (!file.good()){
			this->send_new_error_fatal(index, 404);
			return;
		}
		file.close();
	}
	std::cout << BLUE << "[" << msg.getBody() << "]" << RESET << std::endl;
	int posC = boundary.length();
	while (loop == true) {
		std::cout << "loopstart\n";
		std::string uhm = requested_file;
		uhm = interpreter;
		/* get past the bondary
		because at the end of this loop, thee nd is posC we give it to posa*/
		posa = posC;

		/* posb is at the end of the next boundary. for now, we do 2+ because we need to know if this is the end*/
		posb = msg.getBody().find(boundary, posa) + 2;
		posC = posb + (boundary.length());

		/* posC is the posiiton AFTER the boudnary, and posB the one BEFORE*/

		/* the next boundary*/
		posb -= 2;
		std::string new_boundary = msg.getBody().substr(posb, posC - posb);

		/* compare the new_boundary */
		std::string end_boundary = boundary + "--";
		std::cout << "new[" << GREEN << new_boundary << RESET << "]" << std::endl;
		std::cout << "cop[" << GREEN << end_boundary << RESET << "]" << std::endl;
		if (strcmp(new_boundary.c_str(), end_boundary.c_str()) == 0){
			loop = false;
			// cgi_post_nb(input_pipe, output_pip, msg.getBody().substr(posa, posb - posa - 2), index, msg, requested_file, interpreter);
			std::cout << RED << "[" << msg.getBody().substr(posa, posb - posa - 2) << "]" << RESET << std::endl;
		}
		else {
			/* no -2, because its not the last string*/
			std::cout << GREEN << "[" << msg.getBody().substr(posa, posb - posa) << "]" << RESET << std::endl;
			// cgi_post_nb(input_pipe, output_pip, msg.getBody().substr(posa, posb - posa), index, msg, requested_file, interpreter);
		}
		// break;
	}
	std::cout << "end of CGI_POST" << std::endl;
	//after upload, maybe go back to the previous page
}
