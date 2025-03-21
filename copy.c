#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int agrc,char *argv[])
{
	int fsp = open(argv[1],O_RDONLY);
	if(fsp==-1)
	{
		printf("open sfile fail\n");
		return 0;
	}
	int fdp = open(argv[2],O_RDWR|O_CREAT,0664);
	if(fdp==-1)
	{
		perror("open dfile fail");
		return 0;
	}
	char buffer[4096];
    lseek(fsp,atoi(argv[3]), SEEK_SET);
	lseek(fdp,atoi(argv[3]), SEEK_SET);
	ssize_t bytesRead;
	while((bytesRead=read( fsp, buffer, atoi(argv[4])))>0)
	{
			 write(fdp, buffer, bytesRead);
	}
	close(fsp);
	close(fdp);

	return 0;
}
