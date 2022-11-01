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
			this->send_new_error(sockets[index].fd, 404);
			this->disconnect(index);
			return;
		}
		//when it does not exist, create
		file.open(msg.getPath(), fstream::in | fstream::out | fstream::trunc);
		if (!file.good()){
			this->send_new_error(sockets[index].fd, 404);
			this->disconnect(index);
			return;
		}
		file.close();
	}
	else{//if fiel does exist, check if the path is not a directory
		if (S_ISDIR(msg.getStat().st_mode)){
			this->send_new_error(sockets[index].fd, 404);
			this->disconnect(index);
			return;
		}
	}
	std::cout <<"file successfull\n";
	while (loop == true){
		posa = posb + boundary.length() + 2;
		posb = msg.getBody().find(boundary, posa);
		//check if the end bondary is in there
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
			int file_fd = open(msg.getPath().c_str(), O_RDWR | O_APPEND);
			if (file_fd == -1) {
				this->send_new_error(sockets[index].fd, 404);
				this->disconnect(index);
				return;
			}
			int position = this->tryGetAvailablePosition();
			if (position == -1)
				ft_error("cgi_post");
			sockets[position].fd = file_fd;
			sockets[position].events = POLLOUT;
			sockets[position].revents = 0;
			sockets_info[position].disconnect_after_send = true;
			sockets_info[position].listen = false;
			sockets_info[position].fd_only = false;
			write(file_fd
			, msg.getBody().substr(posa, posb).c_str()
			, msg.getBody().substr(posa, posb).length());
			close(file_fd);
			this->send_new(position, "HTTP/1.1 200 OK\n", output_pip[0]);
			std::cout <<"the end\n";
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
			std::cout <<"[1]\n";
			dup2(output_pip[1], 1);
			dup2(input_pipe[0], 0);
			size_t i = 0;
			size_t len = args.size();
			std::cout <<"[2]\n";
			for (; i < len; ++i) {
				write(input_pipe[1], args[i].c_str(), args[i].length());
				write(input_pipe[1], "\n", 1);
			}
			std::cout <<"[3]\n";
			write(input_pipe[1]
			, msg.getBody().substr(posa, posb).c_str()
			, msg.getBody().substr(posa, posb).length());
			std::cerr << execve(argv[0], (char * const *)argv, (char * const *)envp) << '\n';
			std::cout <<"the end1\n";
			exit(1);
		}
	}
	std::cout <<"the end11\n";
}
