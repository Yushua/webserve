#include <message.hpp>
#include <ft_lib.hpp>
#include <unistd.h>
#include <iostream>
#include <colors.hpp>

void message::init() {

	size_t len = headers_str.length();
	size_t index;

	{/* Get StartLine */
		int start = 0;
		for (index = 0; index < len; ++index) {
			if (headers_str[index] == ' ') {
				startLine.push_back(headers_str.substr(start, index - start));
				start = ++index;
			}
			else if (headers_str[index] == '\n') {
				startLine.push_back(headers_str.substr(start, index - start));
				break;
			}
		}
	}

	if (startLine.size() < 2)
		return;

	{/* Get path and arguments */
		string &url = startLine.at(1);
		size_t len = url.length();
		size_t index = 0;
		bool hadArgs = false;
		for (; index < len; ++index) {
			if (url[index] == '?') {
				hadArgs = true;
				break;
			}
		}
		path = url.substr(0, index);
		if (hadArgs) {/* Get Headers */
			int start = ++index;
			string name, value;
			for (; index < len; ++index) {
				if (url[index] == '&') {
					arguments.push_back(url.substr(start, index - start));
					start = ++index;
				}
			}
			arguments.push_back(url.substr(start, index - start));
		}
	}

	{/* Get Headers */
		bool gettingHeader = true;
		int start = ++index;
		string head, value;
		for (; index < len; ++index) {
			if (gettingHeader && headers_str[index] == ' ') {
				gettingHeader = false;
				head = headers_str.substr(start, index - start);
				start = ++index;
			}
			else if (headers_str[index] == '\n') {
				if (!gettingHeader) {
					gettingHeader = true;
					value = headers_str.substr(start, index - start - 1);
					headers.insert(pair<string, string>(head, value));
					start = ++index;
				}
				else
					break;
			}
		}
	}

	/* Check Message Validity */
	this->check();

	if (contentLength > 0)
		this->state = loadingBody;
	else
		this->state = ready;
}
