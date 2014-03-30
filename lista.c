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
    element *current = head;
    while (current != NULL)
    {
        printf("%d\t",current->val);
        current = current->next;
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

void removeFromList(element **head, int value)
{
    element *curr, *toRem, *tmp;
    curr = *head;
    if (curr->val != value)
    {
        while (curr->next->val != value) curr = curr->next;
        toRem = curr->next;
        curr->next = toRem->next;
        free(toRem);
    }
    else
    {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}


int main()
{
    srand(time(NULL));
    element *head, *curr;
    int toFind, toAdd, toRemove, n;
    head = NULL;

    for (i=1; i<=20; i++)
    {
        n = rand()%20;
        add(&head, n);
    }
    displayList(head);
    printf("\nPodaj jaki element chcesz wyszukac: ");
    scanf("%d",&toFind);
    printf("Szukany element jest %d. elementem na liscie\n\n",searchList(head,toFind));
    printf("Podaj liczbe elementow ktore chcesz wstawic: ");
    scanf("%d",&n);
    for (i=0; i<n; i++)
    {
        printf("Podaj %d. element: ",i+1);
        scanf("%d",&toAdd);
        add(&head, toAdd);
    }
    displayList(head);
    printf("\nPodaj element który chcesz usunac: ");
    scanf("%d",&toRemove);
    removeFromList(&head,toRemove);
    displayList(head);

}
