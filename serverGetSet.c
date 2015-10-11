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
	memset(serverAddr.sin_zero,'\0', sizeof serverAddr.sin_zero);
	bind(welcomeSocket,(struct sockaddr *) &serverAddr,sizeof(serverAddr));

	if(listen(welcomeSocket,5)==0)
		printf("Hellow\n");
	else
		printf("Error\n");
	addr_size = sizeof serverStorage;
	newSocket = accept (welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	if(newSocket == -1)
	{
		perror("accept fail");
		exit(1);
	}
	else
	{	
		memset(buffer,0,sizeof(buffer));

		if(ret = recv(newSocket,buffer,sizeof(buffer),0)<0)
		{
			perror("ReadError");
			exit(1);
		}
		else if (ret ==0)
		{
			getsockopt(welcomeSocket,SOL_SOCKET,SO_REUSEADDR , &serverStorage, &addr_size);
			if (serverStorage == 0)
			{
				printf("Reuseaddr before set :",serverStorage);
			}
			else
			{
				printf("error");
				setsockopt(welcomeSocket, SOL_SOCKET, SO_REUSEADDR, &serverStorage, sizeof 1);
			}
			if(serverStorage  !=0)
			{
				printf ("Reuseaddr after set : ");
			}
			else
			{
				printf("Error");
				getsockopt(welcomeSocket,SOL_SOCKET, SO_REUSEADDR, &serverStorage, &addr_size);
			}
		}
	}
	strcpy(buffer,"HI SIR HAMID\n");
	send(newSocket,buffer,13,0);
	return 0;
}
