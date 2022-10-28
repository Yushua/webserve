#include <webserv.hpp>
#include <colors.hpp>

#define IS_NOT_CHILD fork_res != 0

void webserv::cgi_get(const int index, const message &msg, const string &requested_file, const string &interpreter) {
	int fds[2];
	if (pipe(fds) != 0)
		ft_error("cgi_get");

	int fork_res = fork();
	if (fork_res == -1)
		ft_error("fork");

	if (IS_NOT_CHILD) {
		close(fds[1]);
		
		fcntl(fds[0], O_NONBLOCK);
		this->send_new(index, "HTTP/1.1 200 OK\n", fds[0]);
		
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
		const char **envp = (const char **)new char *[args.size() + 1];
		
		size_t i = 0;
		size_t len = args.size();
		for (; i < len; ++i) {
			envp[i] = args[i].c_str();
		}
		envp[i] = NULL;
		

		dup2(fds[1], 1);
		cerr << execve(argv[0], (char * const *)argv, (char * const *)envp) << '\n';
		exit(1);
	}
}
