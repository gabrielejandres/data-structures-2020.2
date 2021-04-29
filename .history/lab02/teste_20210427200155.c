#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node;
typedef struct Node *PNode;
struct Node
{
    int info;
    PNode link;
    int team_index;
};
struct LinkQueue
{
    int num_of_team;
    PNode f;
    PNode r;
    PNode *index;
};
typedef struct LinkQueue *PLinkQueue;

PLinkQueue create (int n)
{
    PLinkQueue plqu;
    plqu = (PLinkQueue)malloc(sizeof(struct LinkQueue));
    plqu->f = NULL;
    plqu->r = NULL;
    plqu->num_of_team = n;
    plqu->index = (PNode *)malloc(sizeof(PNode)*n);
    int i;
    for (i=0;i<n;i++)
    {
        plqu->index[i] = NULL;
    }
    return plqu;
}
void Enqueue (PLinkQueue plqu, int x, int index)
{
    PNode p;
    p = (PNode)malloc(sizeof(struct Node));
    p->info = x;
    p->team_index = index;
    if (plqu->f == NULL)
    {
        p->link = NULL;
        plqu->f = p;
        plqu->r = p;
        plqu->index[index] = p;
    }
    else 
    {
        if (plqu->index[index] == NULL)
        {
            plqu->r->link = p;
            plqu->r = p;
            p->link = NULL;
            plqu->index[index] = p;
        }
        else
        {
            p->link = plqu->index[index]->link;
            plqu->index[index]->link = p;
            plqu->index[index] = p;
        }
    }
}
int Dequeue (PLinkQueue plqu)
{
    PNode p;
    p = plqu->f;
    if (plqu->f != NULL)
    {
        if (p->link == NULL)
        {
            plqu->f = NULL;
            plqu->r = NULL;
            int temp = p->info;
            plqu->index[p->team_index] = NULL;
            free (p);
            return temp;
        }
        else
        {
            if (p->team_index == p->link->team_index)
            {
                plqu->f = p->link;
                int temp = p->info;
                free(p);
                return temp;
            }
            else
            {
                plqu->index[p->team_index] = NULL;
                plqu->f = p->link;
                int temp = p->info;
                free(p);
                return temp;
            }
        }
    }
    else
    {
        return -1;
    }
}

int main (void)
{
    int i,j;
    int count = 1;
    int t;
    int team[1001][1001];
    int num[1001];
    char str[12];
    scanf ("%d", &t);
    while (t!= 0)
    {
        printf ("Scenario #%d\n", count);
        PLinkQueue teamqueue;
        teamqueue = create(t);
        for (i=0;i<t;i++)
        {
            scanf("%d", &num[i]);
            for (j=0;j<num[i];j++)
            {
                scanf("%d", &team[i][j]);
            }
        }
    /*for (i=0;i<t;i++)
    {
        for (j=0;j<num[i];j++)
        {
            printf("%d ", team[i][j]);
        }
        printf ("\n");
    }*/
        scanf("%s", str);
        while (strcmp(str, "STOP") != 0)
        {
            if (strcmp(str, "ENQUEUE") == 0)
            {
                int temp, ind, ibreak = 0;
                scanf("%d", &temp);
                for (i=0;i<t;i++)
                {
                    for (j=0;j<num[i];j++)
                    {
                        if (temp == team[i][j])
                        {
                            ind = i;
                            ibreak = 1;
                            break;
                        }
                    }
                    if (ibreak) break;
                }
                Enqueue (teamqueue, temp, ind);
            }
            if (strcmp(str, "DEQUEUE") == 0)
            {
                int temp = Dequeue(teamqueue);
                if (temp >= 0)
                {
                    printf("%d\n", temp);
                }
            }
            scanf("%s", str);
        }
        printf ("\n");
        count++;
        scanf ("%d", &t);
    }

    return 0;
}