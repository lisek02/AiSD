#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int size,i;

struct list
{
    int val;
    struct list *next;
};
typedef struct list element;

void randomize(int *tab)
{
    srand(time(NULL));
    int i,tmp,random;
    for (i=0; i<size; i++) tab[i] = i;
    for (i=size-1; i>0; i--)
    {
        random = rand()%i;
        tmp = tab[random];
        tab[random] = tab[i];
        tab[i] = tmp;
    }
}

void displayTab(int *tab)
{
    int i;
    for (i=0; i<(int)size; i++) printf("%d\n",tab[i]);
}

void add(element **head, int value)
{
    element *current;
    current = (element*) malloc(sizeof(element));
    current->val = value;
    current->next = *head;
    *head = current;
}

void displayList(element *first)
{
    element *curr = first;
    while (curr != NULL)
    {
        printf("%d",curr->val);
        curr = curr->next;
    }
}

int main()
{
    element *head, *curr, *toAdd;
    head = NULL;

    add(&head, 15);
    add(&head, 25);
    displayList(head);
}
