#include <message.hpp>

//each msg has their own bool NOW

void message::check()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	// std::vector<std::string> store;//dont' forget to delete it


	for (; itr != end; ++itr)
	{
		// itr->first;
		// itr->second;
		if (itr->first == "Transfer-Encoding:")
		{
			this->unchunk();
		}
		std::cout << itr->first << " " << itr->second << std::endl;
	}
	std::cout << " " << std::endl;

	valid = true;
}

void message::unchunk()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();

	for (; itr != end; ++itr)
	{
		// itr->first;
		// itr->second;
		if (itr->first == "Transfer-Encoding:")
			break;
	}
	std::cout << "hello i am here\n\n";
}
/*

General Header

Request Header

Response Header

Entity Header


GET PUT DELETE POST HEAD


*/
