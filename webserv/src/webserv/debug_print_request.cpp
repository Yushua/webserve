#include <webserv.hpp>
#include <colors.hpp>

void webserv::debug_print_request(const int index, message &msg) {
#ifdef DEBUG
	/* Print out request without body */
	cout << CYAN << "  -~={ " << index << " sent this }=~-\n" << RESET;
	
	{/* Print out the first line */
		vector<string>::const_iterator itr = msg.getStartLine().cbegin();
		vector<string>::const_iterator end = msg.getStartLine().cend();
		for (; itr != end; ++itr)
			cout << ' ' << *itr;
		cout << '\n';
	}
# ifndef NOHEADER
	{/* Print out headers */
		map<string, string>::const_iterator itr = msg.getHeaders().cbegin();
		map<string, string>::const_iterator end = msg.getHeaders().cend();
		for (; itr != end; ++itr)
			cout << itr->first << ": " << itr->second << '\n';
	}
# endif
#else
	(void)index;
	(void)msg;
#endif
}
