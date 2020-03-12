#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<unistd.h>
#include<sys/types.h>
//#include<fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
char cmd[80],token1[20],token2[20],token3[20],token4[20];
int main()
{
	int pid;
	int n;
	while(1)
	{
		printf("\nMyshell$");
		gets(cmd);
		n=sscanf(cmd,"%s%s%s%s",token1,token2,token3,token4);
		if(strcmp(token1,"q")==0)
		{
			exit(0);
		}
		pid=fork();
		if(pid==-1)
		{
			printf("Error\n");
		}
		else if(pid>0)
		{
			wait(NULL);
		}
		else
		{
                       if(strcmp(token1,"list")==0)
                      {
                             list(token3,token2[0]);
                               exit(0);
                      }
                     
			//execlp(token1,token1,NULL);
				      
				
			
		}
	}
}
void list(char *dn, char op)
{
	DIR *dp;
	struct dirent *entry;
	int dc=0,fc=0;

	dp = opendir(dn);
	if(dp==NULL)
	{
		printf("Dir %s not found.\n",dn);
		return;
	}

	switch(op)
	{
	case 'f':
		while(entry=readdir(dp))
		{
			if(entry->d_type==DT_REG)
				printf("%s\n",entry->d_name);
		}
		break;
	case 'n':
		while(entry=readdir(dp))
		{
			
			if(entry->d_type==DT_REG) fc++;
		}
	
		printf("%d Dir(s)\t%d File(s)\n",dc,fc);
		break;
	case 'i':
		while(entry=readdir(dp))
		{
			if(entry->d_type==DT_REG)
				printf("%s\t%d\n",entry->d_name,entry->d_fileno);
		}
                 break;
	}

	closedir(dp);
}



