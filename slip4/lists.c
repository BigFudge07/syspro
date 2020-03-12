#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>


int main() {
    char cmd[80],token1[80],token2[80],token3[80];
    int pid;
    while (1)
    {
        printf("\nMyShell$ ");
        gets(cmd);

        sscanf(cmd,"%s %s %s",&token1,&token2,&token3);

        int pid=fork();

        if(pid==-1) {
            printf("Errror\n");
        }
    else if(pid>0)
    {
        wait(NULL);
    }
    
        else
        {
            if(strcmp(token1,"list")==0){
                list(token3,token2[0]);
                exit(0);
            }
        }
        
    }
    



}

void list(char *dn,char op){
    int count=0;
    DIR *dir;
    dir= opendir(dn);

    struct dirent *entry;


    if(dir==NULL){
        printf("Directory not found\n");
        return;
    }

    switch (op)
    {
    case 'f': while(entry=readdir(dir)){
                if(entry->d_type==DT_REG){
                    printf("%s\n",entry->d_name);
                }

                }
        /* code */
        break;
    
    case 'n':
             while(entry=readdir(dir)){
            if(entry->d_type==DT_REG){
                count++;
            }

    }
        printf("The number of files in the directory are %d\n",count);
        break;
    
    case 'i': 
                        while(entry=readdir(dir)){
		{
			if(entry->d_type==DT_REG)
				printf("%s\t%d\n",entry->d_name,entry->d_fileno);
		}
                 
	}

    
    
    closedir(dir);
    break;
}

}