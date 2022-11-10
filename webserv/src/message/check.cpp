#include <message.hpp>

void message::check()
{
	vector<std::string>::iterator itr_v = startLine.begin();
	vector<std::string>::iterator end_v = startLine.end();
	for (; itr_v < end_v; itr_v++)
	{
		if (*itr_v == "GET")
			checkGet();
		else if (*itr_v == "DELETE")
			checkDelete();
	}
}
