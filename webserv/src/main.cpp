#include <webserv.hpp>

int main() {
	//loop
	map<std::string, webserv*> webservMap;
	configParser(webservMap);//normal name
	map<std::string, webserv*>::iterator it;

	// while (true){
	// 	for (it = webservMap.begin(); it != webservMap.end(); it++)
	// 	{
	// 		it->second->run();
	// 	}
	// }
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
