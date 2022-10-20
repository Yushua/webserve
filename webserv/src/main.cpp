#include <webserv.hpp>

int main() {
	//loop
	map<std::string, webserv*> webservMap;
	configParser(webservMap);//normal name
	map<std::string, webserv*>::iterator it;

	for (it = webservMap.begin(); it != webservMap.end(); it++)
	{
		std::cout << it->first << ':' << std::endl;
		it->second[0].run();
	}
}
