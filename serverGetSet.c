#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
int main()
{
	int welcomeSocket, newSocket, ret;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	int serverStorage;
	socklen_t addr_size;

	welcomeSocket = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(1025);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	addr_size = sizeof serverStorage;
	newSocket = accept (welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

	ret= getsockopt(welcomeSocket,SOL_SOCKET,SO_SNDBUF ,(struct sockaddr *) &serverStorage,(socklen_t *) &addr_size);
	printf("Default : %d\n", serverStorage );
	addr_size = addr_size *2;
	serverStorage = 53894;
	ret= setsockopt(welcomeSocket, SOL_SOCKET, SO_SNDBUF,(struct sockaddr *) &serverStorage, sizeof (serverStorage));
	printf("New :%d\n",serverStorage);

	
	return 0;
}
