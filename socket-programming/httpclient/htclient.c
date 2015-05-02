#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#define SERVER_ADDR "10.1.1.242"

int main(void)
{
	int sockfd;
	struct sockaddr_in dest;
	char buffer[1024];

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Socket creation failed");
		exit(errno);
	}

	dest.sin_family = AF_INET;
	dest.sin_port = htons(80);

	if(inet_aton(SERVER_ADDR,&dest.sin_addr.s_addr)==0)
	{
		perror(SERVER_ADDR);
		exit(errno);
	}

	if(connect(sockfd,(struct sockaddr*)&dest,sizeof(dest))!=0)
	{
		perror("Connect");
		exit(errno);
	}
	strcpy(buffer,"GET / HTTP/1.0\n\n");
	send(sockfd,buffer,sizeof(buffer),0);
	bzero(buffer,sizeof(buffer));
	recv(sockfd,buffer,sizeof(buffer),0);
	printf("Data received %s\n",buffer);

	close(sockfd);
	return 0;
}