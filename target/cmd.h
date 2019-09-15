int shell(char *cmd)
{
	//it change the system() default output, and after capture it in stdin 
	int p[2],newp,pos=0;
	newp = dup(1);
	close(0);
	close(1);
	pipe(p);
	system(cmd);
	dup2(newp,1);
	while(1)
	{
		output[pos] = fgetc(stdin);
		if(output[pos]==EOF)
		{
			break;
		}
		pos++;
	}
}
