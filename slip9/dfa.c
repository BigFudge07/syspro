#include<stdio.h>
#include<stdlib.h>

int nos,noi,nof,final[20],transition[10][10],state[10];
char input[10];
void read() {

    printf("Enter the number of states\n");
    scanf("%d",&nos);
    for(int i=0;i<nos;i++){
        printf("Enter state %d\t",i);
        scanf(" %d",&state[i]);
    }
    printf("Enter the number of inputs\n");
    scanf("%d",&noi);
    for(int i=0;i<noi;i++){
        printf("Enter input %d\t",i+1);
        scanf(" %c",&input[i]);
    }
    printf("Enter the number of final states\n");
    scanf("%d",&nof);
    for(int i=0;i<nof;i++){
        scanf("%d",&final[i]);
    }

    printf("Enter the transition table\n");

    for(int i=0;i<nos;i++){
        for(int j=0;j<noi;j++){
            printf("For (q%d,%c)",state[i],input[j]);
            scanf("%d",&transition[i][j]);
        }
    }

}

void shows() {
    printf("The transition table is \n");
    printf("\t");
    for(int i=0;i<noi;i++){
        printf("%c\t",input[i]);
    }
    printf("\n");

    for(int i=0;i<nos;i++){
        printf("q%d",state[i]);

        for(int j=0;j<noi;j++){
            printf("\tq%d",transition[i][j]);
        }
        printf("\n");
    }
}

void accept() {
    char string[10];
    int current=0;
    printf("Enter the string to be checked\n");
    scanf("%s",string);

    for(int i=0;string[i]!='\0';i++){
        printf("d(q%d,%s)\n",current,string+i);
        current= transition[current][string[i]-input[0]];
    }

    printf("q%d\n",current);

    for(int i=0;i<nof;i++) {
        if(final[i]==current){
            printf("Accepted\n");
            return;
        }
    }
    printf("Rejected\n");


}

int main(void) {
    int ch;
    while(1) {
        printf("Here are your options:\n1:Read Dfa\n2:Show Transition Table\n3:Check Acceptance\n4:Exit\n");
        scanf("%d",&ch);
        switch(ch) {
            case 1: read();
                    break;
            case 2 : shows();
                        break;
            case 3: accept();
                    break;
            case 4:exit(0);
        }
    }
}