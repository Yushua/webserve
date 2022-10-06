#include <webserv.hpp>

void webserv::cgi_get(const int index, const message &msg, const string &requested_file) {
	int child1 = fork();
	if (child1 != 0)
		return;
	
	int fds[2];
	pipe(fds);

	int child2 = fork();
	if (child2 != 0) {
		int ret;
		waitpid(child2, &ret, 0);

		close(fds[1]);
		string script_out = ft_fd_to_str(fds[0]);
		string body = ft_skip_heders(script_out);
		string response = "HTTP/1.1 200 OK\n";
		response += "Content-length: " + ft_to_string(body.length()) + "\n";
		response += script_out;
		this->send(index, response);
		exit(0);
	}
	else {
		const vector<string> &args = msg.getArguments();

		const char *argv[3] = {"/Users/rdrazsky/.brew/bin/python3", requested_file.c_str(), NULL};
		const char **envp = (const char **)new char *[args.size() + 1];
		
		size_t index = 0;
		size_t len = args.size();
		for (; index < len; ++index) {
			envp[index] = args[index].c_str();
		}
		envp[index] = NULL;
		
		
		close(fds[0]);
		dup2(fds[1], 1);
		cerr << execve(argv[0], (char * const *)argv, (char * const *)envp) << '\n';
		exit(1);
	}
}
