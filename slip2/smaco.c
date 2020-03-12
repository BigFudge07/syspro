#include<stdio.h>
long mem[1000];

   int address,instruction,programCounter,lastCounter;

    int opcode,operand1,operand2;

    int cc[6],reg[4];


void load() {

         FILE *fp;
    fp=fopen("min.sm","r");

    while(fscanf(fp,"%d %d",&address,&instruction)!=EOF) {

        if(address==-1){
            programCounter=instruction;

        }
        else
        {
            lastCounter=address;
        mem[address]=instruction;
            
        }
        
       
    }
}

void print() {

    printf("Memory\tInstruction\n");
    for(int i=programCounter;i<=lastCounter;i++){
       printf("%d\t%d\n",i,mem[i]);

    }
}

void run(){
    for(int i=programCounter;i<=lastCounter;i++){
       opcode=mem[i]/10000;
       operand1=(mem[i]/1000)%10;
       operand2=mem[i]%1000;
        printf("%d\n",i);
    switch (opcode)
    {
    case 1: reg[operand1]+=mem[operand2];
            programCounter++;
        break;
    
    case 2: reg[operand1]-=mem[operand2];
            programCounter++;
        break;
    
    case 3: reg[operand1]*=mem[operand2];
            programCounter++;
        break;
    
    case 4: reg[operand1]=mem[operand2];
            programCounter++;
        break;

    case 5: mem[operand2]=reg[operand1];
            programCounter++;
        break;

    case 6: 
    printf("Entered condition code\n");
    for(int i=0;i<5;i++){
                cc[i]=0;
    }

        if(reg[operand1] < mem[operand2]) {
            cc[0]=1;
            printf("0");
        }
        if(reg[operand1] <= mem[operand2]) {
            cc[1]=1;
            printf("1\n");

        }
        if(reg[operand1] == mem[operand2]) {
            cc[2]=1;
            printf("2\n");

        }
         if(reg[operand1] > mem[operand2]) {
            cc[3]=1;
            printf("3\n");

        }
        if(reg[operand1] >= mem[operand2]) {
            cc[4]=1;
            printf("4\n");

        }
      
        if(reg[operand1] != mem[operand2]) {
            cc[5]=1;
            printf("5\n");

        }
        programCounter++;
        break;
    case 7: if(cc[operand1]==1 ) {
            i=operand2;
                        i--;
    }
            else
            {
                programCounter++;
            }
    

    case 8 : reg[operand1]=reg[operand1]/mem[operand2];
            programCounter++;
        break;

    case 9:   printf("\nEnter the contents\n");
			    scanf("%d",&mem[operand2]);
			programCounter++;
			break;
	case 10: printf("\ndisplay the contents:\n");
		    printf("%d",mem[operand2]);
				programCounter++;
				break;
    default:
        break;
    }


        
    }

}

int main() {
    int ch;

    do {
    printf("Here are your choices\n");
    printf("1:Load\n");
    printf("2:Print\n");
    printf("3:Run\n");

    scanf("%d",&ch);


    switch (ch)
    {
    case 1:
    load();
        break;

    case 2:
    print();
        break;

    case 3:
    run();
        break;
    
    default:
        break;
    }

    
   
    }while(ch<3);

    


}