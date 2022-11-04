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
void webserv::cgi_post(const int index, const message &msg, const string &requested_file, const string &interpreter, std::string boundary){
    //open the input pipes
	//information is send to the output files
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
	std::cout <<"file successfull\n";
	while (loop == true){
		posa = posb + boundary.length() + 2;
		posb = msg.getBody().find(boundary, posa);
		//check if the end bondary is in there
		std::cout << YELLOW << msg.getBody() << RESET << std::endl;
		if (msg.getBody().substr(posa, posb).find( boundary + "--") != string::npos){
			//did not find the end boundary
			posb = posb - (boundary.length() + 2);
			loop = false;
		}
		else if (msg.getBody().substr(posa, posb).find(boundary) != string::npos){
			posb = posb - boundary.length() - 2;
		}
		int fork_res = fork();
		if (fork_res == -1)
			ft_error("fork");
		/* Is not child */
		if (fork_res != 0) {
			close(output_pip[1]);
			close(input_pipe[0]);
			close(input_pipe[1]);
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
			size_t i = 0;
			size_t len = args.size();
			for (; i < len; ++i) {
				write(input_pipe[1], args[i].c_str(), args[i].length());
				write(input_pipe[1], "\n", 1);
			}
			write(input_pipe[1]
			, msg.getBody().substr(posa, posb).c_str()
			, msg.getBody().substr(posa, posb).length());
			close(input_pipe[1]);
			std::cerr << execve(argv[0], (char * const *)argv, (char * const *)envp) << '\n';
			exit(1);
		}
	}
	//after upload, maybe go back to the previous page
}
