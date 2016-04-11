#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
void Swap(char **beginn,char **endd)
{
	char *tmp=*beginn;
	*beginn=*endd;
	*endd=tmp;
}
int main()
{
	while(1)
	{
	printf("[myshell@localhost shell]$");
	fflush(stdout);
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	ssize_t _size=read(0,buf,sizeof(buf)-1);//get value from inout
	buf[_size-1]='\0';
//	printf("%s\n",buf);
	char *my_argv[64];
	int end=strlen(buf)-1;
	int begin=0;
	int index=0;
	while(end>=0)
	{
		//end-->begin
		if(isspace(buf[end-1]))//the head of first request  is empty
		{
			my_argv[index++]=&buf[end];
		}
		if(isspace(buf[end]))//last is empty
		{
			buf[end]='\0';
		}
		--end;
	}
	my_argv[index++]=buf;
	my_argv[index]=NULL;
	int start=0;
    end=index-1;
	//swap my_argv[start] my_argv[end]
	while(start<end)
	{
		Swap(&my_argv[start],&my_argv[end]);
		++start;
		--end;
	}
	index=0;
	for(;my_argv[index]!=NULL;index++)
	{
      printf("%s\n",buf);
	}
	if(strcmp(my_argv[0],"cd")==0)//judge is build-in command?
	{
       chdir(my_argv[1]);//menu is change 
       continue;
	}
	//is not build-in command,fork process 
	pid_t id=fork();
	if(id<0)
	{
		perror("fork");
		exit(1);
	}
	else if(id==0)
	{
		execvp(my_argv[0],my_argv);
		exit(1);
	}
	else 
	{
		pid_t ret=waitpid(id,NULL,0);
		if(ret==id)
		{
           // printf("wait successful\n");
		}
	}
	}
	return 0;
}
