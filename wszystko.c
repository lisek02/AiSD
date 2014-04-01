#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,size,size2;


struct list
{
    int val;
    struct list *next;
};
typedef struct list element;

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
    for (i=0; i<size2; i++) tab[i] = i;
    for (i=(size2)-1; i>0; i--)
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
    for (i=0; i<size2; i++) printf("%d\t",tab[i]);
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

/////////////////LISTA///////////////

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

void deleteAVL(avlNode **root, int value)   //////nie dziala!
{
    avlNode *curr, *tmp, *tmp2, *tmp3;
    curr = *root;

    while (curr != NULL)
    {
        if (value <= curr->val) curr = curr->left;
        else curr = curr->right;
    }

    tmp3 = curr;
    if (curr->right != NULL)
    {
        curr = curr->right;
        while (curr->left->left != NULL)
        {
            curr = curr->left;
        }
        tmp = curr->left;
        if (curr->left->right != NULL)
        {
            curr->left = curr->left->right;
        }
        tmp->right = tmp3->right;
        tmp->left = tmp3->left;
        tmp3 = tmp;
        free(tmp);
    }
    else if (curr->left != NULL)
    {
        curr = curr->left;
        while (curr->right->right != NULL)
        {
            curr = curr->right;
        }
        tmp = curr->right;
        if (curr->right->left != NULL)
        {
            curr->right = curr->right->left;
        }
        tmp->right = tmp3->right;
        tmp->left = tmp3->left;
        tmp3 = tmp;
        free(tmp);
    }
    else
    {
        free(curr);
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

int main()
{
    int toFind, toInsert, toDelete;
    element *head, *curr;
    head = NULL;

    ////Tablica
    printf("Podaj liczbe elementow: ");
    scanf("%d",&size);
    size2 = size*1.1;
    int *tab = (int*)malloc(sizeof(int)*size2);
    losuj(tab);
    printf("losowo ulozona tablica:\n");
    wyswietl(tab);

    //WSTAWIANIE
    printf("\n\n----------WSTAWIANIE----------\n");
    //////DO LISTY

    for (i=0; i<size; i++)
    {
        add(&head, tab[i]);
    }
    printf("tablica:\n");
    displayList(head);
    //////DO AVL
    insertion(tab);     //sortowanie rosn¹co tablicy
    avlNode *avlRoot = createAVL(tab, 0, size-1, NULL);
    printf("\ndrzewo AVL preorder:\n");
    preOrder(avlRoot);

    //SZUKANIE
    printf("\n\n----------SZUKANIE----------\n");
    printf("Podaj wartosc ktora chcesz znalesc: ");
    scanf("%d",&toFind);
    //////NA LISCIE
    printf("Szukany element jest %d. elementem na liscie\n",searchList(head,toFind));
    //////W AVL
    printf("W drzewie AVL znajduje sie element : %d\n",searchAVL(avlRoot,toFind));


    //DODAWANIE
    printf("\n\n----------DODAWANIE----------\n");
    printf("Dodaje elementy: ");
    for (i=size; i<size2; i++)
    {
        printf("%d ",tab[i]);
        insertAVL(&avlRoot,tab[i]);
        add(&head, tab[i]);
    }
    printf("\n");
    printf("Lista z dodanymi elementami:\n");
    displayList(head);
    int *tab2 = (int*)malloc(sizeof(int)*size);
    int tmp = 0;
    inOrder(avlRoot, tab2, &tmp);
    printf("\nDrzewo AVL inorder:\n");
    wyswietl(tab2);
    avlRoot = createAVL(tab2, 0, size-1, NULL);
    printf("\nDrzewo AVL preorder:\n");
    preOrder(avlRoot);

    //USUWANIE - nie dziala AVL
    printf("\n\n----------USUWANIE----------\n");
    printf("Podaj wartosc ktora chcesz usunac: ");
    //////Z LISTY
    scanf("%d",&toDelete);
    removeFromList(&head,toDelete);
    printf("\nLista po usunieciu elementu:\n");
    displayList(head);
    //deleteAVL(&avlRoot,toDelete);
    //preOrder(avlRoot);

    //WYSWIETLANIE STRUKTURY ROSNACO
    printf("\n\n----------WYSWIETLANIE STRUKTURY ROSNACO----------\n");
    printf("Lista rosnaca:\n");
    displayList(head);
    printf("\nDrzewo AVL inorder:\n");
    wyswietl(tab2);

    //

    free(tab);
    free(tab2);
}
