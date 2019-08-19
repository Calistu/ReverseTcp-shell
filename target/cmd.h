int shell(char *cmd)
{
	//it change the system() default output, and after capture it in stdin 
	int p[2],newp,ascii=0;
	char mem[30];
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
}
