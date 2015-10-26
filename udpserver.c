#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXBUF 1024

int main (int argc, char * argv[])
{
	int ret;
	int udpSocket;
	int returnStatus=0;
	int addrlen = 0;
	struct sockaddr_in udpServer, udpClient;
	char buf[MAXBUF];

	if (argc <2)
	{
		fprintf(stderr,"Usage: %s <port> \n" ,argv[0]);
		exit(1);
	}
	//pitfall 1
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if( udpSocket == -1)
	{
		fprintf(stderr, "Could not create a socket ! \n");
		exit(1);

	}
	else
	{
		printf("Socket created.\n");
	}
	//pitfall 4
	udpServer.sin_family = AF_INET;
	udpServer.sin_addr.s_addr = htonl(INADDR_ANY);
	udpServer.sin_port = htons(atoi(argv[1]));
	memset(udpServer.sin_zero, '\0',sizeof udpServer.sin_zero);
	returnStatus = bind (udpSocket, (struct sockaddr*) &udpServer, sizeof(udpServer));
	if(returnStatus ==0)
	{
		fprintf(stderr, "bind completed!\n");
		getsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, (struct sockaddr *) &udpClient, &addrlen);
		printf("GetSocket %d\n",getsockopt);
		if(returnStatus >  0)
		printf("Already Set \n");
		
		else
		{
			//pitfall3
			setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, (struct sockaddr *) &udpClient, sizeof udpClient );
			printf("SetSocket %d\n",setsockopt);
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "Could not bind to address !\n");
		close(udpSocket);
		exit(1);
	}

	while(1)
	{
		addrlen = sizeof(udpClient);
		//pitfall 2
		returnStatus = recvfrom(udpSocket, buf, MAXBUF, 0, (struct sockaddr *) & udpClient, &addrlen);

		if(returnStatus ==-1)
		{
			fprintf(stderr, "Could not receive message !\n");
		}
		else
		{
			printf("Received : %s\n", buf);
			strcpy(buf, "Ok");
			//pitfall 1
			returnStatus = sendto (udpSocket,buf,strlen(buf)+1,0,(struct sockaddr *) &udpClient, sizeof(udpClient));

			if(returnStatus == -1)
			{
				fprintf(stderr, "Could not send confirmation!\n");
			}
			else
			{
				printf("Confirmation sent \n");
			}


		}
	}

	
	close(udpSocket);
	return 0;
}


