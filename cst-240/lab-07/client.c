/**************************************
 Name: Rowan Parker
 File: client.c
 Lab/Assignment: CST240-Lab7
 Date: 05/23/2019
**************************************/
#define SIZE 256
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
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
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h> 
#include <fcntl.h>

void error(const char * msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char** argv)
{
	int opt = -1, port = -1;
	char * host = NULL;
	char * ip = NULL;
	
	// test for valid number of arguments
	if (argc <= 2)
	{
		printf("Error: port number and host name or IP address must be provided.\n");
		printf("port number is specified by -p [name]\n");
		printf("host name is specified by -h [host name]\n");
		printf("IP address is specified by -i [address]\n");
		return 1;
	}
	
	// getopt
	while ((opt = getopt(argc, argv, "h:p:i:")) != -1)
	{
		switch(opt)
		{
		case 'h':
			if (optarg == NULL || strcmp(optarg, "-p") == 0 || strcmp(optarg, "-i") == 0)
			{
				printf("Error: %s is an invalid host name.\n", optarg);
			}
			else
			{
				host = (char *)malloc(strlen(optarg) + 1);
				strcpy(host, optarg);
			}
			break;
		case 'p':
			if (optarg == NULL || strcmp(optarg, "-h") == 0 || strcmp(optarg, "-i") == 0)
			{
				printf("Error: no port number given.\n");
			    return 1;
			}
			else
			{
				port = atol(optarg);
			}
			break;
		case 'i':
			if (optarg == NULL || strcmp(optarg, "-p") == 0 || strcmp(optarg, "-h") == 0)  
			{
				printf("Error: %s is an invalid IP address.\n", optarg);
			}
			else
		   	{
			   ip = (char *)malloc(strlen(optarg) + 1);
			   strcpy(ip, optarg);
			}
			break;
		}
	}

	// test for default port
	if (port == -1)
	{
		return 1;
	}

	// test for no host and no ip address
	if (host != NULL && ip != NULL)
	{
		printf("Error: either host name or IP address must be provided, not both.\n");
		return 1;
	}
	// else test for host and ip address
	else if (host == NULL && ip == NULL)
	{
		printf("Error: a host name or IP address must be provided.\n");
		return 1;
	}

	printf("HOST: %s PORT: %d %s\n", host, port, argv[optind]);

	// start socket conncetions
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("Error: something went wrong opening client socket.\n");
	}

	// connect to server
	if (host != NULL)
	{
		struct hostent * server = gethostbyname(host);
		if (server == NULL) 
		{
			error("Error: something went wrong in client, there is no such host.\n");
		}
	
		struct sockaddr_in serv_addr;
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr_list[0],(char *)&serv_addr.sin_addr.s_addr, server->h_length);
		serv_addr.sin_port = htons(port); 

		if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		{
			error("Error: something went wrong, client cannot connect.\n");
		} 	
	}

	int quit = -1;
	while (quit != 0)
	{
		char * cmd_buffer = readline(">> ");
		char * cmd = strtok(cmd_buffer, " ");
		char * filename = strtok(NULL, "\n");
		char buffer[SIZE];
		ssize_t file_descript = -1;
		
		// empty buffer
		bzero(buffer, SIZE);

		if (strcmp(cmd, "put") != 0 && strcmp(cmd, "get") != 0 
			&& strcmp(cmd, "quit") != 0 && strcmp(cmd, "ls") != 0)
		{
			printf("Error: invalid command.\n");
		}
		else
		{
			write(sockfd, cmd, SIZE);
			write(sockfd, filename, SIZE);
	   
			if(strcmp(cmd, "put") == 0)
			{
				printf("Executing %s %s\n", cmd, filename);
				file_descript = open(filename, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
				read(file_descript, buffer, SIZE);
				write(sockfd, buffer, SIZE);
				close(file_descript);
			}
			else if (strcmp(cmd, "get") == 0)
			{
				printf("Executing %s %s\n", cmd, filename);
				file_descript = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
				read(sockfd, buffer, SIZE);
				write(file_descript, buffer, strlen(buffer));
				close(file_descript);
			}
			else if (strcmp(cmd, "quit") == 0)
			{
				quit = 0;
			}
			else
			{
				write(sockfd, cmd, SIZE);
				printf("Executing %s\n", cmd);
				do
				{
					read(sockfd, buffer, SIZE);
					printf("%s\n", buffer);
				}while(strcmp(buffer, "") != 0);
			}
		}

		// free cmd buffer
		free(cmd_buffer);
	}
	
	// close socket
	close(sockfd);
	
	return 0;
}
