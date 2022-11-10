#include <message.hpp>

void message::checkHost(string string)
{
	int ip = 0;
	int i = 0;
	while (string.find(".") != string::npos)
	{
		i = string.find(".");
		if(checkNumber(string, "0123456789") != -1) {
			this->valid = false;
		}
		string.erase(0, i+1);
		ip++;
	}
	if (string.find(":") != string::npos) {
		i = string.find(":");
		if(checkNumber(string, "0123456789") != -1) {
			this->valid = false;
		}
		ip++;
	}
	if (ip != 4)
		this->valid = false;
    this->hostName = string;
	this->valid = true;
}

void message::check()
{
	vector<std::string>::iterator itr_v = startLine.begin();
	vector<std::string>::iterator end_v = startLine.end();
	
	for (; itr_v < end_v; itr_v++)
	{
		if (*itr_v == "GET"){
			map<string, string>::iterator itr = headers.begin();
			map<string, string>::iterator end = headers.end();
			for (; itr != end; ++itr) {
				if (itr->first == "Host:") {
					this->checkHost(itr->second);
				}
				else if (itr->first == "Referer") {
					this->unReferer(itr->second);
				}
			}

		}
		else if (*itr_v == "DELETE"){
			map<string, string>::iterator itr = headers.begin();
			map<string, string>::iterator end = headers.end();
			for (; itr != end; ++itr) {
				if (itr->first == "Host:") {
					this->checkHost(itr->second);
				}
			}
		}
	}
}
