#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct pn {
    char name[20];
    struct pn *next;
}pn;

pn *phead,*plast;

typedef struct kp
{
    char name[20];
    char value[20];
    struct kp *next;
}kp;
kp *khead,*klast;


void createP(char *s) {
    pn *p;
    p=(pn*)malloc(sizeof(pn));
    strcpy(p->name,s);
    p->next=NULL;

    if(phead==NULL){
        phead=p;
    }
    else
    plast->next=p;

    plast=p;
}

void createK(char *s,char *r) {
    kp *p;
    p=(kp*)malloc(sizeof(kp));
    strcpy(p->name,s);
    strcpy(p->value,r);
    p->next=NULL;

    if(khead==NULL){
        khead=p;
    }
    else
    klast->next=p;

    klast=p;
}


void displayP(){
    pn *p;
    printf("\nDisplaying all the parameters\n");
    for(p=phead;p!=NULL;p=p->next){
        printf("%s\n",p->name);
    }
}

void displayK(){
    kp *p;
    printf("\nDisplaying all the keyword parameters\n");
    for(p=khead;p!=NULL;p=p->next){
        printf("%s\t%s\n",p->name,p->value);
    }
}



int main(void){
    char fname[20],buff[80],op1[20],op2[20],op3[20],mnt[20],parameter[20],kp[20];
    char *a,*b,*c,*d;
    char *r=",";
    char *s="=";
    int n,j;
    FILE *fp;
    printf("Enter the filename-\n");
    scanf("%s",fname);
    fp=fopen(fname,"rw");

    printf("THE MDT TABLE IS \n");
    printf("Label\tInstruction\tOperands\n");
    while (fgets(buff,80,fp)!=NULL)         
    {
        n= sscanf(buff,"%s %s %s",op1,op2,op3);
        switch (n)
        {
        case 1:if(strcmp(op1,"MACRO")==0) {
                fgets(buff,80,fp);
                sscanf(buff,"%s %s",op1,op2);
                strcpy(mnt,op1);
                strcpy(parameter,op2);

                for(a=strtok_r(parameter,r,&c);a!=NULL;a=strtok_r(NULL,r,&c)) {
                    if(strchr(a,'=')!=NULL) {
                        for(b=strtok_r(a,s,&d), j=0;b!=NULL;b=strtok_r(NULL,s,&d)) {
                            if(j==0) {
                                strcpy(kp,b);
                                createP(kp);
                                j=1;

                            }
                            else
                            {
                               createK(kp,b);
                            }
                            
                        }
                    }
                    else
                    {
                        createP(a);
                    }
                    


                }
              }
              break;
        case 2: if(strcmp(op1,"MOVER")==0 || strcmp(op1,"MOVEM")==0) {
                printf("- \t %s\t\t%s\n",op1,op2);
        }
        else
        {
            printf("%s\t%s\n",op1,op2);
        }
        
            
            break;
        case 3: printf("%s\t %s\t\t%s\n",op1,op2,op3);
        default:
            break;
        }

    }

    printf("The macro name is %s",mnt);
    displayP();
    displayK();
    

}