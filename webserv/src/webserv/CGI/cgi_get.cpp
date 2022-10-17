#include <webserv.hpp>

void webserv::cgi_get(const int index, const message &msg, const string &requested_file, const string &interpreter) {
	int fds[2];
	pipe(fds);

	int child = fork();
	if (child == -1)
		ft_error("fork");

	if (child != 0) {
		int ret;
		waitpid(child, &ret, 0);

		close(fds[1]);
		string script_out = ft_fd_to_str(fds[0]);
		close(fds[0]);
		string body = ft_skip_heders(script_out);
		string response = "HTTP/1.1 200 OK\n";
		response += "Content-length: " + ft_to_string(body.length()) + "\n";
		response += script_out;
		(void)index;
		// this->send_new_file(index, response);
		return;
	}
	else {
		const vector<string> &args = msg.getArguments();

		const char *argv[3] = {interpreter != "" ? interpreter.c_str() : requested_file.c_str(), requested_file.c_str(), NULL};
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
