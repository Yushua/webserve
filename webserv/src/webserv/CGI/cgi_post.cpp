#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <algorithm>
#include <string>

//check if this body is chunked

#define IS_NOT_CHILD fork_res != 0

//CGI turns the body, or the part of the body between the boundries into CGI and let it run
//Through EXECVE
void webserv::cgi_post_nb(int *input_pipe, int *output_pip, std::string send, const int index, const message &msg, const string &requested_file, const string &interpreter) {
	std::cout << "in here == " << YELLOW << send << RESET << std::endl;
	int fork_res = fork();
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
		//if execve fails, return 500
		exit(1);
	}
	return ;
}

void webserv::cgi_post(const int index, const message &msg, const std::string &requested_file, const std::string &interpreter, std::string boundary) {
	boundary = "--" + boundary;
	int posa = 0;
	int posb = 0;
	std::string str = "";
	bool loop = true;
	ofstream file;
	if (!msg.getStatState())//need to check if this is a chunk file, meaning it exist because a chunk has been send there
	{
		//if its folder
		if (S_ISDIR(msg.getStat().st_mode)) {
			this->send_new_error_fatal(index, 404);
			return;
		}
		//when it does not exist, create
		file.open(msg.getPath(), fstream::in | fstream::out | fstream::trunc);
		if (!file.good()) {
			this->send_new_error_fatal(index, 404);
			return;
		}
		file.close();
	}
	// string_string_split(boundary, posa, msg);
	int posC = boundary.length();
	bool check = false;
	while (loop == true) {
		int input_pipe[2];
		if (pipe(input_pipe) != 0)
			ft_error("cgi_pot input");
		int output_pip[2];
		if (pipe(output_pip) != 0)
			ft_error("cgi_post output");
		std::cout << "loop\n";
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
		if (strcmp(new_boundary.c_str(), end_boundary.c_str()) == 0) {
			std::string tmp = msg.getBody().substr(posa + 2, posb - posa - 2);
			std::cout << RED << "tmp == [" << tmp << "]" << RESET << std::endl;
			cgi_post_nb(input_pipe, output_pip, tmp, index, msg, requested_file, interpreter);
			break ;
		}
		else {
			/* no -2, because its not the last string*/
			std::string tmp = msg.getBody().substr(posa + 2, posb - posa - 2);
			std::cout << GREEN << "tmp == [" << tmp << "]" << RESET << std::endl;
			cgi_post_nb(input_pipe, output_pip, tmp, index, msg, requested_file, interpreter);
			check = true;
		}
	}
}
