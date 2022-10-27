#include <webserv.hpp>

int webserv::tryGetAvailablePosition() {
	if (this->availablePositions.size() == 0)
		return -1;
	
	int availablePosition = this->availablePositions.top();
	this->availablePositions.pop();

	return availablePosition;
}

void webserv::returnPosition(int position) {
	if (0 <= position && position <= SOCKET_COUNT_MAX)
		this->availablePositions.push(position);
}
