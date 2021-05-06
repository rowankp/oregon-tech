//test_server
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
		error("Error: unable to open socket in server.\n");
	}

	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)	
	{
		error("Error: unable to perform binding in server.\n");
	} 

	listen(sockfd,5); 

	struct sockaddr_in cli_addr;

	socklen_t clilen = sizeof(cli_addr);

	int clientfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (clientfd < 0)
	{
		error("Error:something went wrong on server accept\n."); 
	}
	
	char buffer[256];
	bzero(buffer,256);

    ssize_t n = read(clientfd, buffer, 255);
	if (n < 0) 
	{
		error("Error: reading from socket\n.");
	}
   
	printf("Here is the message: %s\n", buffer);
 
	n = write(clientfd,"I got your message", 18);
	if (n < 0) 
	{
		error("Error: something went wrong in writing to socket in server.\n");
	}

	close(clientfd); 
	close(sockfd);

	return 0;
}
