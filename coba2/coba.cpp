// Test coba coba buat file
// Socket Client
// Rzm77

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

#pragma GCC diagnostic ignored "-Wwrite-strings"

int wadah[200];
int pcount;
char *pry1;

int main()
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "hello dari client";
	struct sockaddr_in servaddr;
	
	// Pembuatan Socket
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0 ,sizeof(servaddr));
	
	// Mengisi Server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	socklen_t len; // tidak bisa pakai int
	int n;
	
	sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM,(const struct sockaddr *)&servaddr, sizeof(servaddr));
	
	printf("hello message sent.\n");
	
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr,&len);
	
	buffer[n] = '\0';

	// pry1 = strtok(buffer,",");
	//  while (pry1 != 0 && pcount <= 5)
    // {
	// if (pcount == 1) wadah[1] = atoi(pry1);
	// else if(pcount == 2) wadah[2] = atoi(pry1);
	// else if(pcount == 3) wadah[3] = atoi(pry1);
	// else if(pcount == 4) wadah[4] = atoi(pry1);
	// else if(pcount == 5) wadah[5] = atoi(pry1);
	// pcount++;
    // }
    // if (pcount == 6) pcount = 1;

	printf("Data dari server\n");
	printf("%s",buffer);
	// printf("%d\n%d\n%d\n%d\n%d",wadah[0],wadah[1],wadah[2],wadah[3],wadah[4]);
	// wadah = atoi(buffer);
	// printf("Server : %d\n",wadah);
	
	close(sockfd);
	return 0;
}
