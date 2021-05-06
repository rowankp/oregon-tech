// test_client
#include <dirent.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#define PORT 50000 

void error(const char *msg)
{
	perror(msg);
	exit(1);
} 

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("Error: something went wrong  opening client socket\n.");
	}

	struct hostent *server = gethostbyname("localhost");
	if (server == NULL) 
	{
		error("ERROR, no such host\n");
	}
	
	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr_list[0],(char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(PORT); 

	if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("Error: client cannot connect\n");
	} 

	char buffer[256];
	bzero(buffer,256);
	strcpy(buffer,"My brain hurts!");

	ssize_t n = write(sockfd,buffer,strlen(buffer));
	if (n < 0)
	{
		error("ERROR writing to socket");
	}

	bzero(buffer,256);

	n = read(sockfd,buffer,255);

	if (n < 0)
	{
		error("ERROR reading from socket");
	}

	printf("%s\n",buffer);

	close(sockfd);

	return 0;
}
