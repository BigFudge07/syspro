
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
long mem[1000];
int reg[4];
int cc[]={0,0,0,0,0,1};
int pc;
int lc;
void load();
void print();
void execute();
void accept();
int flag=0;
int main()
{
	int ch;
	while(1)
	{
		printf("\n.menu:");
		printf("\n1.Load:");
		printf("\n2.Print:");
		printf("\n3.Run:");
		printf("\n4.Accept:");
		printf("\n5.trace:");
		printf("\n6.exit:");
		printf("\nEnter the choice:");
		scanf("%d",&ch);          
		switch(ch)
		{
			case 1:load();
			       break;
			case 2:print();
			       break;
			case 3:execute();
			       break;
			case 4:accept();
			       break;
			case 5:trace();
			       break;
			case 6:exit(0);
		}
	}
}
void load()
{          
	char str[80];
	printf("\nEnter the File name:");
	scanf("%s",str);
	int address;
	int content;
	FILE *fp;
	fp=fopen(str,"r");
	while(!feof(fp))
	{
		fscanf(fp,"%d%d",&address,&content);
		if(address==-1)
		{
			pc=content;
		}
		else
		{
			lc=address;
			mem[address]=content;
		}
	}
	fclose(fp);	
}
void print()
{
	int i;
	printf("\naddress\tcontent:");
	for(i=pc;i<=lc;i++)
	{
		printf("\n%d\t%d",i,mem[i]);
	}
}
void execute()
{
	int i;
	int opcode;
	int op1;
	int op2;
	for(i=pc;i<=lc;i++)
	{
		opcode=mem[pc]/10000;
		op1=(mem[pc]/1000)%10-1;
		op2=mem[pc]%1000;
		switch(opcode)
		{
			case 1:reg[op1]+=mem[op2];
			       pc++;
			       break;
			case 2:reg[op1]-=mem[op2];
			       pc++;
			       break;
			case 3:reg[op1]=reg[op1]*mem[op2];
			       pc++;
			       break;
			case 4:reg[op1]=mem[op2];
			       pc++;
			       break;
			case 5:mem[op2]=reg[op1];
			       pc++;
			       break;
			case 6:
			       if(reg[op1]<mem[op2])cc[0]=1;
			       if(reg[op1]<=mem[op2])cc[1]=1;
			       if(reg[op1]==mem[op2])cc[2]=1;
			       if(reg[op1]>mem[op2])cc[3]=1;
			       if(reg[op1]>=mem[op2])cc[4]=1;
			       pc++;
			       break;
			case 7:if(cc[op1]==1)
				       pc=op2;
			       else
			       {
				       pc++;
				       for(i=0;i<5;i++)
					       cc[i]=0;
			       }
			       break;
			case 8:reg[op1]=reg[op1]/mem[op2];
			       pc++;
			       break;
			case 9:printf("\nEnter the contents\n");
			       scanf("%d",&mem[op2]);
			       pc++;
			       break;
			case 10:printf("\ndisplay the contents:\n");
				printf("%d",mem[op2]);
				pc++;
				break;
			case 0:flag=0;
			       exit(0);
		}
		if(flag==1)
		{
			printf("\n Areg=%d,Breg=%d,Creg=%d,Dreg=%d",reg[0],reg[1],reg[2],reg[3]);
		}
	}
}
void accept()
{
	int address,content;
	int i;
	FILE *fp;
	char fname[30];
	printf("\nEnter the File name:");
	scanf("%s",fname);
	fp=fopen(fname,"w");
	do
	{
		printf("\nEnter the address:");
		scanf("%d",&address);
		printf("\nEnter the content:");
		scanf("%d",&content);
		fprintf(fp,"%d\t%d\n",address,content);
	}while(address!=-1);
	fclose(fp);
}
void trace()
{
	flag=1;
	execute();
}
