#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h> 
#include <sys/wait.h>
void waiting(void);
int pram_check(char *sfile,int argc,int pronum)
{
	//if(pronum==0)
	// {
	  //    pronum=3;
		 
	// }
	int file=open(sfile,O_RDONLY);
	if(file==-1)
	{
		close(file);
		perror("file open fail\n");
		return 0;
	}
	if(argc<3)
	{
		perror("agrc error\n");
	  return 0;	
	}
	if(!(pronum>0&&pronum<=100))
	{
		printf("process number error! procss  number:%d\n",pronum);
		return 0;
	}
    close(file);
	return 1;

}
int block_cur(char* sfile,int pronum)
{
  		FILE *fp = NULL;
		int fileSize = 0;			
		fp = fopen(sfile , "r");
		if(NULL == fp)
	    {
		return 0;
		}
		fseek(fp, 0L, SEEK_END);
   	 fileSize = ftell(fp);
		if(fileSize%pronum==0)
		{
					return fileSize/pronum;
		}
		else
		{
			return (fileSize/pronum+1);
		}
}
void process_create(char *sfile,char *dfile,int blocksize,int pronum)
{
	int i=0;
	pid_t pid;
	for(i;i<pronum;i++)
	{
		pid=fork();
		if(pid==0)
		{
			break;
		}
	}
	if(pid>0)
	{
		waiting();
	}
	else if(pid==0)
	{
		char pos[10];
		sprintf(pos,"%d",(blocksize*i));
		char bolck[10];
		sprintf(bolck,"%d",blocksize); 
		execl("/home/zhuzeyv/colin4/copy","copy",sfile,dfile,pos,bolck,NULL);
	}
	 else
	 {
	    perror("frok error");
	 }
}
void waiting(void)
{
    int child;
    while( (child=waitpid(-1,NULL,WNOHANG))!=-1)
    {
		if(child==0)
		{

		}
		else
		{
			printf("remove child prcess : %d\n",child);
		}
		sleep(1);
	}
		                
}
int main(int argc ,char *argv[])
{
	if(argv[3]==0)
	{
		argv[3]='3';
	}
	int a=pram_check(argv[1],argc,atoi(argv[3]));
	if(a==1)
	{
		int blockszie = block_cur(argv[1],atoi(argv[3]));
		printf("bs: %d\n", blockszie);
		process_create(argv[1],argv[2],blockszie,atoi(argv[3]));
	}
	else
	{
		printf("parm error!\n");
	}
	return 0;
}

