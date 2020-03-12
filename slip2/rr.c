//ROUND ROBIN SCHEDULING ALGORITHM



#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct n
{
    int arrivalT, burstT, exitT;
    char pname[20];
    struct n *next;
} node;
int timeQuantum;
node *head = NULL, *last = NULL;

void create(char pname[20], int at, int bt)
{
    node *p;
    p = (node *)malloc(sizeof(node));
    strcpy(p->pname, pname);
    p->arrivalT = at;
    p->burstT = bt;
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

void swap(node *s, node *r)
{

    char temp1[20];
    int temp;

    strcpy(temp1, s->pname);
    strcpy(s->pname, r->pname);
    strcpy(r->pname, temp1);

    temp = s->arrivalT;
    s->arrivalT = r->arrivalT;
    r->arrivalT = temp;

    temp = s->burstT;
    s->burstT = r->burstT;
    r->burstT = temp;
}

void sort()
{
    node *p, *q;
    int maxAT = 0, totalt = 0, endT;
    for (p = head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (p->arrivalT > q->arrivalT)
            {
                swap(p, q);
            }
        }
        totalt = totalt + p->burstT;

        if (p->arrivalT >= maxAT)
        {
            maxAT = p->arrivalT;
        }
    }

    p = head;
    endT = p->arrivalT;

    while (endT != totalt)
    {

        if (p->burstT > timeQuantum)
        {
            if (endT + timeQuantum < maxAT)
            {
                q = p;
                while (1)
                {
                    if (endT + timeQuantum < q->next->arrivalT)
                    {
                        node *n = (node *)malloc(sizeof(node));
                        strcpy(n->pname, p->pname);
                        n->arrivalT = 0;
                        n->burstT = p->burstT - timeQuantum;
                        n->next = q->next;
                        q->next = n;
                        p->burstT = timeQuantum;
                        break;
                    }
                    else
                    {
                        if (q->next != NULL)
                            q = q->next;
                    }
                }
            }
            else
            {
                create(p->pname, 0, (p->burstT - timeQuantum));
                p->burstT = timeQuantum;
            }
        }
        endT = endT + p->burstT;
        p->exitT = endT;
        p = p->next;
    }
}

void calc()
{
    int at[20], bt[20], et[20], wt[20], tat[20], n = 0, breaker = 0;
    char pname[20][20];

    node *p, *q;

    for (p = head; p != NULL; p = p->next, breaker = 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (strcmp(pname[i], p->pname) == 0)
            {
                breaker = 1;
            }
        }

        if (breaker == 0)
        {
            strcpy(pname[n], p->pname);
            at[n] = p->arrivalT;
            bt[n] = p->burstT;
            et[n] = p->exitT;
            for (q = p->next; q != NULL; q = q->next)
            {
                if (strcmp(p->pname, q->pname) == 0)
                {
                    if (q->exitT > p->exitT)
                    {
                        et[n] = q->exitT;
                    }
                    bt[n] = bt[n] + q->burstT;
                }
            }
            tat[n] = et[n] - at[n];
            wt[n] = tat[n] - bt[n];
            printf("%s\t%d\t%d\t%d\t%d\t%d\n", pname[n], at[n], bt[n], et[n], tat[n], wt[n]);
            n++;
        }
    }
}

void print()
{

    node *current, *p = head, *q = head;

    for (current = head; current->next != NULL; current = current->next)
        ;

    printf("Exit Times -\t");
    printf("%d\t\t", p->arrivalT);

    for (int i = 0; i <= current->exitT; i++)
    {
        if (i == p->exitT)
        {

            printf("%d\t\t", p->exitT);
            p = p->next;
        }
    }
    printf("\n");
    printf("Pname\t\t");
    for (int i = 0; i <= current->exitT; i++)
    {
        if (i == q->exitT)
        {

            printf("\t%s\t", q->pname);
            q = q->next;
        }
    }

    printf("\n");
}

int main(void)
{

    int n, at, bt;
    char pname[20];
    printf("How many processes do you want to input?\n");
    scanf("%d", &n);
    printf("Enter the time quantum-:\n");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < n; i++)
    {
        printf("Enter the Process name, Arrival time, Burst time of process %d\n", i + 1);
        scanf("%s%d%d", pname, &at, &bt);
        create(pname, at, bt);
    }

    sort();
    calc();
    print();
}
