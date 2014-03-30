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
    element *current, *new_el, *tmp;
    current = *head;
    new_el = (element*) malloc(sizeof(element));
    new_el->val = value;
    if (current == NULL)
    {
        *head = new_el;
        new_el->next = NULL;
    }
    else if (value <= current->val)
    {
        *head = new_el;
        new_el->next = current;
    }
    else
    {
        while ((current->next != NULL) && (current->next->val <= value))
        {
            current = current->next;
        }
        new_el->next = current->next;
        current->next = new_el;
    }
}

void displayList(element *head)
{
    element *curr = head;
    while (curr != NULL)
    {
        printf("%d\n",curr->val);
        curr = curr->next;
    }
}

int searchList(element *head, int value)
{
    element *curr = head;
    int i = 1;
    if (curr != NULL)
    {
        while ((curr->val != value) && (curr->next != NULL))
        {
            curr = curr->next;
            i++;
        }
        if (curr->val == value) return i;
        else return 0;
    }

}

int main()
{
    srand(time(NULL));
    element *head, *curr, *toAdd;
    int toFind;
    head = NULL;

    for (i=1; i<=20; i++)
    {
        int n = rand()%20;
        add(&head, n);
    }
    displayList(head);
    scanf("%d",&toFind);
    printf("%d",searchList(head,toFind));
}
