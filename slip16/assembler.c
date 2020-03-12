#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int cnt=1;
char mnemonics[20][11]= {"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};

char declaration[20][3]={"DC","DS"};

char registers[20][5]={"AREG","BREG","CREG","DREG"};

char assembler_directive[20][7]={"START","END","ORIGIN","EQU","LTORG"};

typedef struct node{
    char name[20];
    int location;
    int value;
    int count;
    struct node *next;

}NODE;
NODE *head,*last;


void addSymbol(char *s) {
    NODE *p;

    p = (NODE*)malloc(sizeof(NODE));


    strcpy(p->name,s);
    p->count=cnt;
    p->next=NULL;

    cnt++;

    if(head == NULL) {
        head=p;
    }
    else
    {
        last->next=p;
    }
    last=p;

}

NODE  * searchSymbol(char *s) {
    NODE *p;
    p=head;

    while(p!=NULL){
        if(strcmp(p->name,s)==0) {
            return p;
        }
        p=p->next;
        
    }
    return NULL;

}

int searchM(char *s) {

    for (int i=0;i<10;i++) {
        if(strcmp(mnemonics[i],s)==0){
            return i;
        }

    }
}
int searchR(char *s) {

    for (int i=0;i<4;i++) {
        if(strcmp(registers[i],s)==0){
            return i+1;
        }
        
    }
}

void displaySymbol() {
    NODE *p;
    printf("SR.NO\tNAME\tADDRESS\tVALUE\n");
    for(p=head;p!=NULL;p=p->next){
        printf("%d\t%s\t%d\t%d\n",p->count,p->name,p->location,p->value);
    }
}
int main(void){
    int n,locationCounter,mn,rg;
    char fname[20],buff[80],op1[20],op2[20],op3[20],op4[20];
    FILE *fp;
    NODE *p;
    printf("Enter the file name");
    scanf("%s",fname);
    fp=fopen(fname,"rw");
    while (fgets(buff,80,fp)!=NULL)
    {
        n=sscanf(buff,"%s %s %s %s",op1,op2,op3,op4);
        switch (n)      
        {
        case 1: if(strcmp(op1,"STOP")==0){
                printf("(IS,00)\n");
                locationCounter++;
                }
                else if(strcmp(op1,"END")==0)
                {
                    printf("(AD,02)\n");
                }
                
            
            break;
        
        case 2: 
                 
                        
                if(strcmp(op1,"START")==0){
                printf("(AD,01) (C,%s)\n",op2);
                locationCounter=atoi(op2);
                 }

                 else if(strcmp(op1,"PRINT")==0) {
                            p=searchSymbol(op2);
                        if(p==NULL) {
                             addSymbol(op2);                        } 
                     printf("(IS,10) (S,%d)\n",p->count);
                    locationCounter++;
                     }

                 break;


        case 3:
                if(strcmp(op2,"DS")==0 || strcmp(op2,"DC")==0) {
                 p=searchSymbol(op1);
                 if(p==NULL) {
                    addSymbol(op1);
                 } 
                 else{    
                 p->location=locationCounter;
                 p->value=atoi(op3);
                 }
                 if(strcmp(op2,"DS")==0){
                     printf("(DL,01) (C,%d)\n",p->value);
                 }   
                 else 
                 printf("(DL,02) (C,%d)\n",p->value);


                }
                else if(mn=searchM(op1)){
                     rg=searchR(op2);
                    p=searchSymbol(op3);
                    if(p==NULL) {
                    addSymbol(op3);
                 }     
                 p=searchSymbol(op3);

                 printf("(IS,%d) (%d) (S,%d)\n",mn,rg,p->count);
                }




                locationCounter++;
                break;



        default:
            break;
        }

    
    }
    

printf("DISPLAYING THE SYMBOL TABLE\n");
displaySymbol();
}
