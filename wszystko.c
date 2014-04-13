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

struct bst
{
    struct bst *left;
    struct bst *right;
    int val, bf;
};
typedef struct bst bstNode;

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

void randomizeToDelete(int *tab, int *tabToDelete)
{
    srand(time(NULL));
    int i,random;
    for (i=0; i<size2-size; i++)
    {
        random = rand()%(size2-i);
        tabToDelete[i] = tab[random];
        tab[random] = tab[size2-i];
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


bstNode *newbstNode(int value)  /////tworzenie nowego wezla
{
    bstNode *node = (bstNode*) malloc(sizeof(bstNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bstNode*  searchbstNode(bstNode *wezel, int wartosc)
{
 if (wezel == NULL || wartosc == wezel->val)
          return wezel;

 if (wartosc < wezel->val)
          return searchbstNode(wezel->left, wartosc);
 else
          return searchbstNode(wezel->right, wartosc);
}

void insertBST(bstNode **root, int value)
{
    if (*root == NULL)
    {
        bstNode *toInsert = newbstNode(value);
        *root = toInsert;
        return;
    }
    bstNode *curr;
    curr = *root;
    if (value <= curr->val)
    {
        if (curr->left == NULL)
        {
            bstNode *toInsert = newbstNode(value);
            curr->left = toInsert;
        }
        else
        {
            curr = curr->left;
            insertBST(&curr, value);
        }
    }
    else
    {
        if (curr->right == NULL)
        {
            bstNode *toInsert = newbstNode(value);
            curr->right = toInsert;
        }
        else
        {
            curr = curr->right;
            insertBST(&curr, value);
        }
    }
}

void deleteBST(bstNode *wezel)
 {
 bstNode *pom;
 if (wezel != NULL)  {
            deleteBST(wezel -> left);
            deleteBST(wezel -> right);
            pom=wezel;
        wezel=NULL;
        free(pom);
 }
}

void preOrderbst(bstNode *root)    ////wyœwietlanie w porzadku preorder
{
    if (root == NULL) return;
    printf("%d\t",root->val);
    preOrderbst(root->left);
    preOrderbst(root->right);
}

int heightBST(bstNode *root)
{
 if(root==NULL)return 0;
 int h1 = heightBST(root->left);
 int h2 = heightBST(root->right);
 if (h1>h2) return 1+h1;
 else return 1+h2;
}

void inOrderbst(bstNode *root, int *tab, int *i)    ////wyœwietlanie w porzadku inorder
{
    if (root == NULL) return;
    inOrderbst(root->left, tab, i);
    tab[*i] = root->val;
    (*i)++;
    inOrderbst(root->right, tab, i);
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

int heightAVL(avlNode *root)
{
    if(root == NULL) return 0;
    int h1 = heightAVL(root->left);
    int h2 = heightAVL(root->right);
    if (h1>h2) return 1+h1;
    else return 1+h2;
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
        }
        else
        {
            curr = curr->right;
            insertAVL(&curr, value);
        }
    }
}

void deleteAVL(avlNode **root, int value)   //Nie usuwa, a powinno
{
    avlNode *curr, *tmp, *parentOfCurrent, *toReplace;
    curr = *root;

    while (curr->val != value)
    {
        if (value <= curr->val) curr = curr->left;
        else curr = curr->right;
    }

    if ((curr->left == NULL) && (curr->right == NULL))
    {
        curr->val = 123;
        free(curr);
    }
    else if ((curr->right != NULL) && (curr->left == NULL))
    {
        toReplace = curr->right;
        curr->val = 123;
        free(curr);
        curr = toReplace;
    }
    else if ((curr->left != NULL) && (curr->right == NULL))
    {
        toReplace = curr->left;
        curr->val = 123;
        free(curr);
        curr = toReplace;
    }
    else
    {
        tmp = curr;
        curr = curr->right;
        while (curr->left != NULL) curr = curr->left;
        tmp->val = curr->val;
        curr->val = 123;
        free(curr);
    }
}

void deleteAVL2(avlNode **root, int value)   //Nie usuwa, a powinno
{
    avlNode *curr, *tmp, *tmp2, *parentOfCurrent, *toReplace;
    curr = *root;
    int dir = 0;        ////0 - lewo, 1 - prawo
    parentOfCurrent = NULL;

    while (curr->val != value)
    {
        parentOfCurrent = curr;
        if (value <= curr->val)
        {
            curr = curr->left;
            dir = 0;
        }
        else
        {
            curr = curr->right;
            dir = 1;
        }
    }

    if ((curr->left == NULL) && (curr->right == NULL))
    {
        curr = NULL;
        free(curr);
    }
    else if (parentOfCurrent == NULL)
    {
        if ((curr->right != NULL) && (curr->left == NULL))
        {
            free(root);
            *root = curr->right;
        }
        else if ((curr->left != NULL) && (curr->right == NULL))
        {
            free(root);
            *root = curr->left;
        }
        else
        {
            curr = curr->right;
            while (curr->left != NULL) curr = curr->left;
            tmp = *root;
            tmp->val = curr->val;
            curr = NULL;
            free(curr);
        }
    }
    else if ((curr->right != NULL) && (curr->left == NULL))
    {
        if (dir == 0) parentOfCurrent->left = curr->right;
        else parentOfCurrent->right = curr->right;
        curr = NULL;
        free(curr);
    }
    else if ((curr->left != NULL) && (curr->right == NULL))
    {
        if (dir == 0) parentOfCurrent->left = curr->left;
        else parentOfCurrent->right = curr->left;
        curr = NULL;
        free(curr);
    }
    else
    {
        tmp = curr;
        curr = curr->right;
        while (curr->left != NULL) curr = curr->left;
        *tmp = *curr;

        //tmp->val = curr->val;
        if (dir == 0) parentOfCurrent->left = tmp;
        else parentOfCurrent->right = tmp;
        //curr->val = 123;
        curr = NULL;
        free(curr);
    }
}

/*void deleteAVL3(avlNode **root, int value)   //To jest wersja w której probuje przerobiC LO Tarnow
{
    avlNode *curr, *tmp, *tmp2, *parentOfCurrent, *toReplace;
    avlNode *Y, *Z;
    curr = *root;
    int dir = 0;        ////0 - lewo, 1 - prawo
    parentOfCurrent = NULL;

    while (curr->val != value)
    {
        parentOfCurrent = curr;
        if (value <= curr->val)
        {
            curr = curr->left;
            dir = 0;
        }
        else
        {
            curr = curr->right;
            dir = 1;
        }
    }
    if ((curr->right == NULL) || (curr->left == NULL))
    {
        Y = curr;
    }
    else
    {
        Y = curr;
        Y = Y->right;
        while (Y->left != NULL) Y = Y->left;
    }
    if (Y->left != NULL) Z = Y->left;
    else Z = Y->right;
    if (Z != NULL)

}*/



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

void removeAVL(avlNode *root)
{
    avlNode *toRemove;
    if (root == NULL) return;
    removeAVL(root->left);
    removeAVL(root->right);
    toRemove = root;
    free(toRemove);
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
    //////DO BST
    bstNode *bstRoot = newbstNode(tab[0]);
    for(i=1;i<size;i++) insertBST(&bstRoot,tab[i]);
    printf("\ndrzewo BST preorder:\n");
    preOrderbst(bstRoot);
    //////DO AVL
    insertion(tab);     //sortowanie rosn¹co tablicy
    avlNode *avlRoot = createAVL(tab, 0, size-1, NULL);
    printf("\ndrzewo AVL preorder:\n");
    preOrder(avlRoot);
    printf("\nwysokosc drzewa: %d",heightAVL(avlRoot));

    //SZUKANIE
    printf("\n\n----------SZUKANIE----------\n");
    printf("Podaj wartosc ktora chcesz znalesc: ");
    scanf("%d",&toFind);
    //////NA LISCIE
    printf("Szukany element jest %d. elementem na liscie\n",searchList(head,toFind));
    //////W BST
    bstNode *Found = searchbstNode(bstRoot,toFind);
    printf("W drzewie BST znajduje sie element : %d\n",Found->val);
    //////W AVL
    printf("W drzewie AVL znajduje sie element : %d\n",searchAVL(avlRoot,toFind));


    //DODAWANIE
    printf("\n\n----------DODAWANIE----------\n");
    printf("Dodaje elementy: ");
    for (i=size; i<size2; i++)
    {
        printf("%d ",tab[i]);
        insertAVL(&avlRoot,tab[i]);
        insertBST(&bstRoot,tab[i]);
        add(&head, tab[i]);
    }
    printf("\n");
    printf("Lista z dodanymi elementami:\n");
    displayList(head);
    printf("\nDrzewo BST preorder:\n");
    preOrderbst(bstRoot);
    ////AVL
    int *tab2 = (int*)malloc(sizeof(int)*size2);
    int tmp = 0;
    inOrder(avlRoot, tab2, &tmp);
    //printf("\nDrzewo AVL inorder:\n");
    //wyswietl(tab2);
    avlRoot = createAVL(tab2, 0, size2-1, NULL);
    printf("\nDrzewo AVL preorder:\n");
    preOrder(avlRoot);

    //USUWANIE - nie dziala AVL
    /*printf("\n\n----------USUWANIE----------\n");
    for (i=1; i<=3; i++)
    {
        printf("\nPodaj wartosc ktora chcesz usunac: ");
        //////Z LISTY
        scanf("%d",&toDelete);
        removeFromList(&head,toDelete);
        printf("\nLista po usunieciu elementu:\n");
        displayList(head);
        printf("\nDrzewo AVL po usunieciu elementu:\n");
        deleteAVL2(&avlRoot,toDelete);
    }
        tmp = 0;
        inOrder(avlRoot, tab2, &tmp);
                    //printf("\nDrzewo AVL inorder:\n");
                    //wyswietl(tab2);
        avlRoot = createAVL(tab2, 0, size2-4, NULL);
        preOrder(avlRoot);
    */

    //USUWANIE
    printf("\n\n----------USUWANIE----------\n");
    int *tabToDelete = (int*)malloc(sizeof(int)*size2-size);
    randomizeToDelete(tab2, tabToDelete);
    printf("Usuwam elementy: ");
    for (i=0; i<(size2-size); i++)
    {
        printf("%d ",tabToDelete[i]);
        removeFromList(&head,tabToDelete[i]);
        deleteAVL2(&avlRoot,tabToDelete[i]);
    }
    /////LISTA
    printf("\nLista po usunieciu elementu:\n");
    displayList(head);
    /////DRZEWO AVL
    printf("\nDrzewo AVL po usunieciu elementu:\n");
    tmp = 0;
    inOrder(avlRoot, tab, &tmp);        /////wypisuje elementy do tablicy tab[], ponieważ po usunieciu elementow ich liczba zmniejszyla sie do size. tab[] - rozmiar size; tab2[] - rozmiar size2
    avlRoot = createAVL(tab, 0, size-1, NULL);
    preOrder(avlRoot);

    //WYSWIETLANIE STRUKTURY ROSNACO
    printf("\n\n----------WYSWIETLANIE STRUKTURY ROSNACO----------\n");
    printf("Lista rosnaca:\n");
    displayList(head);
    int *tab3 = (int*)malloc(sizeof(int)*size2);
    tmp = 0;
    inOrderbst(bstRoot, tab3, &tmp);
    printf("\nDrzewo BST inorder:\n");
    wyswietl(tab3);
    printf("\nDrzewo AVL inorder:\n");
    wyswietl(tab2);

    printf("\n\n------USUWANIE LISTY I DRZEW--------\n");
    deleteBST(bstRoot);
    removeAVL(avlRoot);

    //

    free(tab);
    free(tab2);
    free(tab3);
}
