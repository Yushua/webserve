#include <webserv.hpp>
#include <colors.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// static void train_post(){
// 	std::string tmp = "----WebKitFormBoundaryAf55pAxy5GYiuaMT";
// 	std::string boundary = "--" + tmp;
// 	std::cout << "hey[" << boundary  << "]" << std::endl;
// 	std::ifstream infile("root/cgo-bin/cgi-test.txt");
// 	std::string line;
// 	bool post_start = false;
// 	char **argv;
// 	int i = 0;
// 	int y = 0;
// 	while (line != boundary + "--" && std::getline(infile, line)){
// 		if (post_start == false){
// 			if (line == boundary){
// 				post_start = true;
// 				i++;
// 			}
// 			else{
// 				std::cout << "error, boundary unfound" << std::endl;
// 			}

// 		}
// 		else {
// 			if (line == boundary){
// 				post_start = false;
// 				//start fork
// 			}
// 			else{
// 				continue;
// 				//store string
// 			}
// 		}
// 	}
// 	//make the forks, using the I, telling me how many forks.
// 	//and also using that to WHAT they HAVE TO FORK there
// }

int main() {
	//loop
	// train_post();
	map<std::string, webserv*> webservMap;
	configParser(webservMap);//normal name
	map<std::string, webserv*>::iterator it;

	while (true){
		for (it = webservMap.begin(); it != webservMap.end(); it++)
		{
			it->second->run();
		}
	}
}

// int main()
// {
// 	webserv server;
// 	server.config_listen_to_port("4242");
// 	server.config_add_cgi_option("py", "/usr/bin/python");
// 	server.config_add_cgi_option("lol", "");
// 	server.config_add_error_page(400, "root/error_pages/400.html");
// 	server.config_add_error_page(403, "root/error_pages/403.html");
// 	server.config_add_error_page(404, "root/error_pages/404.html");
	
// 	server.config_new_redirect("/", "root");
// 	server.config_set_body_size("/", "0");
// 	server.config_add_method("/", "GET");
// 	server.config_add_method("/", "HEAD");
// 	server.config_set_dir_behavior("/", "root/index.html");

// 	server.config_new_redirect("/pictures", "root/pictures");
// 	server.config_set_body_size("/pictures", "12mb");
// 	server.config_add_method("/pictures", "GET");
// 	server.config_add_method("/pictures", "HEAD");
// 	server.config_add_method("/pictures", "POST");
// 	server.config_add_method("/pictures", "DELETE");
// 	server.config_set_dir_behavior("/pictures", "error");

// 	while (true){
// 		server.run();
// 	}
// }
