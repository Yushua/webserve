#include <webserv.hpp>

void webserv::cgi_get(const int fd, const string &requested_file) {

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
		cout << '{' << response << "}\n";
		this->send(fd, response);
		exit(0);
	}
	else {
		const char *argv[3] = {"/Users/rdrazsky/.brew/bin/python3", requested_file.c_str(), NULL};
		const char *envp[1] = {NULL};
		close(fds[0]);
		dup2(fds[1], 1);
		cerr << execve(argv[0], (char * const *)argv, (char * const *)envp) << '\n';
		exit(1);
	}
}
