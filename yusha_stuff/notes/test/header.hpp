#define PORT 4006
#define READ_BUFFER_SIZE 4242
#define MAX_CLIENT 10
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

#include <string>
#include <iostream>
#include <fcntl.h>
