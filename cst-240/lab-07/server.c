/**************************************
 Name: Rowan Parker
 File: server.c
 Lab/Assignment: CST 240-Lab7
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
#include <stdbool.h> 
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
	
	if (argc < 2)
	{
		printf("Error: port number is required.\n");
		return 1;
	}

	while ((opt = getopt(argc, argv, "p:")) != -1)
	{
		switch(opt)
		{
		case 'p':
			port = atol(optarg);
			if (port < 0)
			{
				printf("Error: invalid port number.\n");
				return 1;
			}
			break;
		default:
			printf("Error: invalid server option.\n");
			return 1;
		}
	}

	printf("PORT: %d\n", port);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0)
	{
		error("Error: unable to open socket in server.\n");
	}

	// define socket options
	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	// bind socket and establish server
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)	
	{
		error("Error: unable to perform binding in server.\n");
	} 

	// listen for a client to connect
	listen(sockfd, 5); 

	// set up and accept a connection
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	int clientfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (clientfd < 0)
	{
		error("Error: something went wrong on server accept\n."); 
	}

	char cmd[SIZE];
	char filename[SIZE];
	char buffer[SIZE];
    ssize_t file_descript = -1;
	int quit = -1;

	while(quit != 0)
	{
		bzero(buffer, SIZE);

		// get command
		read(clientfd, cmd, SIZE);
		// get filename
		read(clientfd, filename, SIZE);
		
		printf("Executing %s...\n", cmd);

		// store files from client
		if (strcmp(cmd, "put") == 0)
		{
			file_descript = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			read(clientfd, buffer, SIZE);
			write(file_descript, buffer, strlen(buffer));
			close(file_descript);
		}
		// send files to client
		else if (strcmp(cmd, "get") == 0)
		{
			file_descript = open(filename, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
			read(file_descript, buffer, SIZE);
			write(clientfd, buffer, SIZE);
			close(file_descript);
		}
		// quit
		else if (strcmp(cmd, "quit") == 0)
		{
			quit = 0;
		}
		// list files in directory
		else 
		{
			printf("1");
			DIR * d;
			struct dirent * dir;
			d = opendir(".");
			printf("2");
			if (d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					write(clientfd, dir->d_name, SIZE);
				}
			   	closedir(d);
				write(clientfd, "", SIZE);
			}
			else
			{
				//strcpy(buffer, "-- no files found --");
			}
		}
	}

	// close client connection
	close(clientfd); 
	// close socket
	close(sockfd);
	
	return 0;
}
