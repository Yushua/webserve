#include <webserv.hpp>
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

	if (startLine.size() != 3) return;

	string &url = startLine.at(1);
	string og_path = startLine.at(1);
	url.clear();

	{/* Ugly way to remove too many '/' */
		
		size_t og_path_len = og_path.length();
		bool last_was_slash = false;
		for (size_t i = 0; i < og_path_len; i++) {
			char c = og_path[i];
			if (c == '?')
				break;
			else if (c == '/') {
				if (!last_was_slash
					&& (i + 1 != og_path_len))
					url += c;
				last_was_slash = true;
			}
			else {
				url += c;
				last_was_slash = false;
			}
		}
		if (url[url.length() - 1] == '/')
			url.erase(url.length() - 1);
	}

	{/* Get path and arguments */
		size_t len = url.length();
		size_t index = 0;
		for (; index < len; ++index);

		path = url.substr(0, index);
		
		/* Get arguments */
		len = og_path.length();
		if (index < len) {
			int start = ++index;
			string name, value;
			for (; index < len; ++index) {
				if (og_path[index] == '&') {
					arguments.push_back(og_path.substr(start, index - start));
					start = ++index;
				}
			}
			arguments.push_back(og_path.substr(start, index - start));
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
					headers.insert(pair<string, string>(ft_to_lower(head), value));
					start = ++index;
				}
				else
					break;
			}
		}
	}

	this->check();
	if (!valid) return;

	/* Does the message have a chunked body? */
	const string Transfer_Encoding = this->getHeader("transfer-encoding:");
	if (Transfer_Encoding == "chunked") {
		this->chunked = true;
		this->state = loadingBody;
		this->contentLength = 0;
		this->chunk_buffer = this->body_str;
		this->body_str.clear();
		return;
	}
	
	/* Does the message even have a body? */
	const string Content_Length = this->getHeader("content-length:");
	if (Content_Length != "") {
		if (Content_Length.find_first_not_of("0123456789") != string::npos)
			{ valid = false; return; }
		contentLength = atoi(Content_Length.c_str());
		this->state = loadingBody;
	}
	else
		this->state = ready;
}
