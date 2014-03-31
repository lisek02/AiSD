#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,size;

struct avl
{
    struct avl *p;
    struct avl *left;
    struct avl *right;
    int val, bf;
};
typedef struct avl avlNode;

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
    for (i=0; i<(int)size; i++) printf("%d\t",tab[i]);
}

void insertion(int *tab)
{
    int j,i,x;
    for(j = size - 2; j >= 0; j--)
    {
        x = tab[j];
        i = j + 1;
        while((i < size) && (x > tab[i]))
        {
            tab[i - 1] = tab[i];
            i++;
        }
        tab[i - 1] = x;
    }
}

int split(int *tab, int right, int left)
{
    int n;
    n = left+(right-left)/2;
    return n;
}
/////////////////AVL///////////////

avlNode *newNode(int value)
{
    avlNode *node = (avlNode*) malloc(sizeof(avlNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

avlNode *createAVL(int *tab, int left, int right)
{
    if (left > right) return NULL;
    int n = left+(right-left)/2;
    avlNode *root = newNode(tab[n]);
    root->left = createAVL(tab, left, n-1);
    root->right = createAVL(tab, n+1, right);
    return root;
}

void preOrder(avlNode* root)
{
    if (root == NULL) return;
    printf("%d\t",root->val);
    preOrder(root->left);
    preOrder(root->right);
}

int main()
{
    printf("Podaj liczbe elementow:\n");
    scanf("%d",&size);
    int *tab = (int*)malloc(sizeof(int)*size);
    losuj(tab);
    wyswietl(tab);
    printf("\n-----------------\n");
    ////AVL
    insertion(tab);
    avlNode *avlRoot = createAVL(tab, 0, size-1);
    preOrder(avlRoot);

    free(tab);

}
