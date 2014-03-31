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

avlNode *newNode(int value)  /////tworzenie nowego wezla
{
    avlNode *node = (avlNode*) malloc(sizeof(avlNode));
    node->val = value;
    node->p = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

avlNode *createAVL(int *tab, int left, int right, avlNode *parent)  ////tworzenie drzewa z tablicy
{
    if (left > right) return NULL;
    int n = left+(right-left)/2;
    avlNode *root = newNode(tab[n]);
    root->left = createAVL(tab, left, n-1, root);
    root->right = createAVL(tab, n+1, right, root);
    root->p = parent;
    return root;
}

int searchAVL(avlNode *root, int value)
{
    avlNode *curr;
    curr = root;

    while((curr->val != value) && (curr->right != NULL) && (curr->left != NULL))    /////dopracowac!!!
    {
        if (value <= curr->val) curr = curr->left;
        else curr = curr->right;
    }
    if (curr->val == value) return curr->val;
    else return -1;
}

void insertAVL(avlNode **root, int value)
{
    if (*root == NULL)
    {
        avlNode *toInsert = newNode(value);
        *root = toInsert;
        size++;
        return;
    }
    avlNode *curr;
    curr = *root;
    if (value <= curr->val)
    {
        if (curr->left == NULL)
        {
            avlNode *toInsert = newNode(value);
            curr->left = toInsert;
            size++;
        }
        else
        {
            curr = curr->left;
            insertAVL(&curr, value);
        }
    }
    else
    {
        if (curr->right == NULL)
        {
            avlNode *toInsert = newNode(value);
            curr->right = toInsert;
            size++;
        }
        else
        {
            curr = curr->right;
            insertAVL(&curr, value);
        }
    }
}

void preOrder(avlNode *root)    ////wyœwietlanie w porzadku preorder
{
    if (root == NULL) return;
    printf("%d\t",root->val);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(avlNode *root, int *tab, int *i)    ////wyœwietlanie w porzadku inorder
{
    if (root == NULL) return;
    inOrder(root->left, tab, i);
    tab[*i] = root->val;
    (*i)++;
    inOrder(root->right, tab, i);
}

void inOrderTab(avlNode *root, int *tab)
{

}

int main()
{
    int toFind, toInsert;

    ////Tablica
    printf("Podaj liczbe elementow: ");
    scanf("%d",&size);
    int *tab = (int*)malloc(sizeof(int)*size);
    losuj(tab);
    printf("losowo ulozona tablica:\n");
    wyswietl(tab);
    printf("\n-----------------\n");

    //AVL
    insertion(tab);
    //////avlNode *avlRoot = NULL;
    avlNode *avlRoot = createAVL(tab, 0, size-1, NULL);
    printf("drzewo AVL preorder:\n");
    preOrder(avlRoot);

    //////szukanie elementu
    printf("\nPodaj wartosc ktora chcesz znalesc: ");
    scanf("%d",&toFind);
    printf("Znaleziony element: %d\n",searchAVL(avlRoot,toFind));


    //////dodawanie elementu
    printf("\nPodaj wartosc ktora chcesz dodac: ");
    scanf("%d",&toInsert);
    insertAVL(&avlRoot,toInsert);
    int *tab2 = (int*)malloc(sizeof(int)*size);
    int tmp = 0;
    inOrder(avlRoot, tab2, &tmp);
    printf("wyswietlanie tablicy z drzewem AVL przepisanym inroder:\n");
    wyswietl(tab2);
    avlRoot = createAVL(tab2, 0, size-1, NULL);
    printf("\ndrzewo AVL preorder:\n");
    preOrder(avlRoot);

    //preOrder(avlRoot);

    free(tab);
    free(tab2);

}
