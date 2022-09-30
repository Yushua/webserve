#include <message.hpp>

//each msg has their own bool NOW

void message::check()
{
	// vector<string>::iterator itr_v = startLine.begin();
	// vector<string>::iterator end_v = startLine.end();
	// for (; itr_v < end_v; itr_v++)
	// {
	// 	std::cout << *itr_v << " " << std::endl;
	// }
	
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();
	// std::vector<std::string> store;//dont' forget to delete it
	std::string Host;
	for (; itr != end; ++itr)
	{
		if (itr->first == "Transfer-Encoding:")
		{
			this->unchunk();
		}
		else if (itr->first == "Host:")
		{
			if (this->unHost(itr->second))
				Host = itr->first;
			else
				valid = false;
		}
		else if (itr->first == "Referer:")
		{
			if (this->unRefer(itr->second, Host))
				valid = true;
			else
				valid = false;
		}
		// std::cout << itr->first << " " << itr->second << std::endl;
	}
	std::cout << " " << std::endl;

	// if error == 400
	// 	valid = false;
	valid = true;
}

void message::unchunk()
{
	map<string, string>::iterator itr = headers.begin();
	map<string, string>::iterator end = headers.end();

	for (; itr != end; ++itr)
	{
		if (itr->first == "Transfer-Encoding:")
			break;
	}
	std::cout << "hello i am here\n\n";
}

bool message::unHost(string string)
{
	//127.0.0.1:4243
	string = " ";
	return true;
}

bool message::unRefer(string string, std::string host)
{
	//http://127.0.0.1:4243/page2.html
	string = " ";
	host = " ";
	return true;
}

/*

General Header

Request Header

Response Header

Entity Header


GET PUT DELETE POST HEAD


*/
