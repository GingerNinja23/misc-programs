#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

int main(int Count, char *Strings[])
{
	int sockfd;
	struct sockaddr_in addr;
	char buffer[1024];

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Socket creation failed");
		exit(errno);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr  = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))!= 0)
	{
		perror("socket-bind");
		exit(errno);
	}

	if(listen(sockfd,20)!=0)
	{
		perror("error listening");
		exit(errno);

	}

	else
	{
		printf("Listening\n");
	}

	int clientfd;
	struct sockaddr_in client_addr;
	int addrlen = sizeof(client_addr);

	clientfd = accept(sockfd,(struct sockaddr*)&client_addr,&addrlen);
	printf("%s:%d",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

	bzero(&buffer,sizeof(buffer));
	//strcpy(buffer,"Hello World\n");

	recv(clientfd,buffer,sizeof(buffer),0);

	int num1,num2;
	char c;
	sscanf(buffer,"%d%c%d",&num1,&c,&num2);
	printf("\ndata is %d--%c--%d",num1,c,num2);
	//printf("Data received %s\n",buffer);
	//send(clientfd,buffer,13,0);


	close(sockfd);
	return 0;
}