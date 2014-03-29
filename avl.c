#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,size;


void losuj(int *tab)
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

void wyswietl(int *tab)
{
    int i;
    for (i=0; i<size; i++) printf("%d\n",tab[i]);
}

int main()
{
    //int size,i;
    printf("Podaj liczbe elementow:\n");
    scanf("%d",&size);
    size*=1.1;
    int *tab = (int*)malloc(sizeof(int)*size);
    losuj(tab);
    wyswietl(tab);
}
