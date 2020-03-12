#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct node {

    char name[20];
    int used,defined,redefined;
    struct node *next;

}NODE;

NODE *head,*last;
char is[20][20]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};

void addSymbol(char *s) {

    NODE *p;
    p=(NODE*)malloc(sizeof(NODE));

    strcpy(p->name,s);
    p->next=NULL;


    if(head==NULL) {
        head=p;
    }

    else
    {
        last->next=p;
    }
    last=p;
}

NODE * searchSymbol(char *s) {

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
    NODE *p;
    p=head;

    for(int i=0;i<10;i++){
        if(strcmp(is[i],s)==0)
        return i;
    }

}

void displayError() {

    NODE *p;
    for(p=head;p!=NULL;p=p->next){
        if(p->used==1 && p->defined==0){
            printf("Symbol %s used but not defined\n",p->name);
        }

        if(p->redefined==1) {
            printf("Redeclaration of symbol %s\n",p->name);
        }

        if(p->defined==1 && p->used==0) {
            printf("Symbol %s defined but not used\n",p->name);
        }
    }
}
int main(void) {
    char fname[20],buff[80],op1[20],op2[20],op3[29],op4[20];
    int n,mn;
    FILE *fp;
    NODE *p;
    printf("Enter the file name-:\n");
    scanf("%s",fname);

    fp= fopen(fname,"rw");

    while(fgets(buff,80,fp)!=NULL) {

        n=sscanf(buff,"%s %s %s %s",op1,op2,op3,op4);
        switch (n)
        {
        case 2: if(strcmp(op1,"START")==0) {}
            else {
                p=searchSymbol(op2);
                if(p==NULL) {
                    addSymbol(op2);
                    p=searchSymbol(op2);
                    p->used=1;
                }
                else {
                    p->used=1;
                }
            }
            break;
        
        case 3: if(strcmp(op2,"DC")==0 || strcmp(op2,"DS")==0){

                p=searchSymbol(op1);
                if(p==NULL) {
                    addSymbol(op1);
                    p=searchSymbol(op1);
                    p->used=1;
                }
                else if(p->defined==1) {
                    p->redefined=1;
                }
                else
                {
                    p->defined=1;
                }
                

        }
        
        else {
                p=searchSymbol(op3);
                if(p==NULL){
                    addSymbol(op3);
                    p=searchSymbol(op3);
                    p->used=1;
                }
                else{
                    
                    p->used=1;
                }
        }
                break;
        
        case 4: p=searchSymbol(op1);
                if(p==NULL) {
                    addSymbol(op1);
                    p=searchSymbol(op1);
                    p->defined=1;
                }
                else if(p->defined==1) {
                    p->redefined=1;
                }
                else
                {
                    p->defined=1;
                }

                p=searchSymbol(op4);
                if(p==NULL) {
                    addSymbol(op4);
                    p=searchSymbol(op4);
                    p->used=1;
                }
              
                break;
        default:
            break;
        }
    }
    printf("DISPLAYING ERRORS\n");
    displayError();
}