#include <message.hpp>

void message::check()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	for (; itr != end; ++itr)
	{
		// itr->first;
		// itr->second;
		std::cout << itr->first << " " << itr->second << std::endl;
	}
	std::cout << " " << std::endl;
	valid = true;
}
