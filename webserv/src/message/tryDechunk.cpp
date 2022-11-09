#include <message.hpp>
#include <colors.hpp>

static size_t hextoi(string &chunk_buffer, int nl_pos) {
	
	char c;
	size_t n = 0;
	size_t base = 1;
	
	while (nl_pos >= 0) {
		c = chunk_buffer[nl_pos--];
		switch (c) {
			case 'a':case 'A': n += 10 * base;break;
			case 'b':case 'B': n += 11 * base;break;
			case 'c':case 'C': n += 12 * base;break;
			case 'd':case 'D': n += 13 * base;break;
			case 'e':case 'E': n += 14 * base;break;
			case 'f':case 'F': n += 15 * base;break;
			default:           n += (c - '0') * base;break;
		}
		base *= 16;
	}
	
	return n;
}

void message::tryDechunk() {
	
	start:

	size_t end = chunk_buffer.length();
	
	if (dechunk_looking_for_chunk && end > 2) {

		--end;

		int nl_pos = -1;
		char c;
		for (size_t i = 0; i < end; i++) {
			switch (c = chunk_buffer[i]) {
			case '0':case '1':case '2':case '3':case '4':case '5':
			case '6':case '7':case '8':case '9':case 'a':case 'A':
			case 'b':case 'B':case 'c':case 'C':case 'd':case 'D':
			case 'e':case 'E':case 'f':case 'F':
				continue;

			case '\r':
				if (chunk_buffer[i + 1] != '\n')
					{ state = msgError; return; }
			case '\n':
				nl_pos = i;
				break;
			
			default: state = msgError; return;
			}
			if (nl_pos != -1)
				break;
		}

		dechunk_chunk_size = hextoi(chunk_buffer, nl_pos - 1);
		// cout << BLUE  << chunk_buffer << RESET << '\n';
		if (c == '\r')
			chunk_buffer.erase(0, nl_pos + 2);
		else
			chunk_buffer.erase(0, nl_pos + 1);
		// cout << CYAN  << chunk_buffer << RESET << '\n';
		dechunk_looking_for_chunk = false;
		goto start;
	}
	else if (end >= dechunk_chunk_size) {
		if (dechunk_chunk_size == 0) {
			state = ready;
			return;
		}
		body_str.append(chunk_buffer, 0, dechunk_chunk_size);
		switch (chunk_buffer[dechunk_chunk_size + 1]) {
			case '\r':
				if (chunk_buffer[dechunk_chunk_size + 2] != '\n')
					{ state = msgError; return; }
				chunk_buffer.erase(0, dechunk_chunk_size + 2);
				break;
			case '\n':
				chunk_buffer.erase(0, dechunk_chunk_size + 1);
				break;
			default: state = msgError; return;
		}
		dechunk_looking_for_chunk = true;
		goto start;
	}
}
