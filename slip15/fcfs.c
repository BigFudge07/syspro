

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct n   
{

    char pname[20];
    int accessTime, burstTime, exitTime, startTime, tat, waitTime;
    struct n *next;
} node;
static int totalwt = 0, totaltat = 0;
node *head, *last;

void create(char pname[20], int at, int bt)
{

    node *p;
    p = (node *)malloc(sizeof(node));
    strcpy(p->pname, pname);
    p->accessTime = at;
    p->burstTime = bt;
    p->next = NULL;

    if (head == NULL)
    {
        head = p;                          
    }
    else
    {
        last->next = p;                     
    }

    last = p;                               
}

void sort() 
{

    node *p, *q;
    int t;
    char name[20];

    for (p = head; p != NULL; p = p->next) 
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (p->accessTime > q->accessTime)           
            {
                strcpy(name, p->pname);
                strcpy(p->pname, q->pname);
                strcpy(q->pname, name);

                t = p->accessTime;
                p->accessTime = q->accessTime;
                q->accessTime = t;

                t = p->burstTime;
                p->burstTime = q->burstTime;
                q->burstTime = t;
            }
        }
    }
}

void calc()
{
    node *p, *q;
    for (p = head; p != NULL; p = p->next)
    {
        if (p == head)
        {
            p->startTime = p->accessTime; 
            p->exitTime = p->burstTime;     
            p->tat = p->exitTime - p->accessTime;
            p->waitTime = p->tat - p->burstTime;
        }
        for (q = p->next; q != NULL; q = q->next)
        {

            if (q->accessTime > p->exitTime)
            {
                q->startTime = q->accessTime;
            }
            else
                q->startTime = p->exitTime; 
            q->exitTime = q->startTime + q->burstTime;
            q->tat = q->exitTime - q->accessTime;
            q->waitTime = q->tat - q->burstTime;

            break;
        }
    }
}

void print() 
{
    node *p;
    printf("Pname\tArrival\tBurst\tStart\texit\ttat\twait\n");
    for (p = head; p != NULL; p = p->next)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p->pname, p->accessTime, p->burstTime, p->startTime, p->exitTime, p->tat, p->waitTime);
        totaltat += p->tat;
        totalwt += p->waitTime;
    }
}

void printg() 
{

    node *current, *p = head, *q = head;

    for (current = head; current->next != NULL; current = current->next)  
        ;

    printf("Exit Times -\t");
    printf("%d\t\t", p->startTime);

    for (int i = 0; i <= current->exitTime; i++)
    {
        if (i == p->exitTime)
        {

            printf("%d\t\t", p->exitTime);
            p = p->next;
        }
    }
    printf("\n");
    printf("Pname\t\t");
    for (int i = 0; i <= current->exitTime; i++)
    {
        if (i == q->exitTime)
        {

            printf("\t%s\t", q->pname);
            q = q->next;
        }
    }

    printf("\n");
}

int main(void)
{

    char pname[20];
    int at, bt, n;
    printf("How many processes?\n");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)                     
    {
        printf("Enter the process name and arrival time and burst time\n");
        scanf("%s%d%d", pname, &at, &bt);
        create(pname, at, bt);
    }
    sort();
    calc();
    print();
    printf("\nAverage Waiting time:%f", (float)totalwt / n);   
    printf("\nAverage Turn Around Time:%f\n", (float)totaltat / n);
    printg();
}
