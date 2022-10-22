#include <webserv.hpp>

// static void unchunkCheck()
// {
// 	std::string string = "4\r\nWiki\r\n6\r\npedia \r\n3\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n";
// 	std::cout << "==\n" << string << "==/n" << std::endl;
// 	std::cout << "==\n" << string << "==/n" << std::endl;
// 	bool chunkStatus = false;
// 	std::string tmp;
// 	int y = 0;
// 	for (int i = 0; static_cast<unsigned long>(i) < string.length();){
// 		i = 0;
// 		i = string.find("\r");
// 		tmp = string.substr(0, i);
// 		if (chunkStatus == false){
// 			if (tmp.find_first_not_of("0123456789") == string::npos){
// 				std::cout << " ERROR 404, NOT A NUMBER" << std::cout;
// 				return ;
// 			}
// 			y = atoi(tmp.c_str());
// 			chunkStatus = true;
// 		}
// 		else if (chunkStatus == true){
// 			if (y != tmp.length()){
// 				std::cout << " ERROR 404, LENGHT NOT THERE" << std::cout;
// 				return ;
// 				// this->send_new_error(sockets[index].fd, 404);
// 				// this->disconnect_socket(index);
// 				// return;
// 			}
// 			chunkStatus = false;
// 		}
// 		string.erase(0, i + 2);
// 	}
// }

// static void unchunInput()
// {
// 	std::string string = "4\r\nWiki\r\n6\r\npedia \r\n3\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n";
// 	std::cout << "==\n" << string << "==/n" << std::endl;
// 	std::cout << "==\n" << string << "==/n" << std::endl;
// 	bool chunkStatus = false;
// 	std::string tmp;
// 	int y = 0;
// 	for (int i = 0; static_cast<unsigned long>(i) < string.length();){
// 		i = 0;
// 		i = string.find("\r");
// 		if (chunkStatus == false){
// 			chunkStatus = true;
// 		}
// 		else if (chunkStatus == true){
// 			chunkStatus = false;
// 			//file << string.substr(0, i);
// 		}
// 		string.erase(0, i + 2);
// 	}
// }


int main() {
	//loop
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
