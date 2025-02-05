/* Exercise 6-4. Write a program that prints the distinct words in 
   its input sorted into decreasing order of frequency of occurrence. 
   Precede each word by its count. */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100

/* the tree node */
struct tnode { 
    char *word; /* points to the text */
    int count; /* number of occurrences */
    struct tnode *left; /* left child */
    struct tnode *right; /* right child */
};

struct tnode *addtree(struct tnode *, char *);
int treesize(struct tnode *p);
int treearray(struct tnode *p, struct tnode *array[], int index);
void my_qsort(struct tnode *v[], int left, int right);
void treeprint(struct tnode *v[], int n); 
int getword(char *, int);

/* word frequency count */
int main() {
    struct tnode *root;
    char word[MAXWORD];
    int size;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    size = treesize(root);
    struct tnode **array = malloc(size * sizeof(struct tnode *));
    treearray(root, array, 0); 
    my_qsort(array, 0, size-1);
    treeprint(array, size);
    return 0;
}

struct tnode *talloc(void);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) { /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++; /* repeated word */
    else if (cond < 0) /* less than into left subtree */
        p->left = addtree(p->left, w);
    else /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* estimate the number of words */
int treesize(struct tnode *p){
    if (p == NULL)
        return 0;
    return 1 + treesize(p->left) + treesize(p->right);
}

/* populate trees on array */
int treearray(struct tnode *p, struct tnode *array[], int index){
    if (p == NULL)
        return index;
    array[index++] = p;
    index = treearray(p->left, array, index);
    index = treearray(p->right,array, index);
    return index;
}

/* qsort: sort v[left]...v[right] into decreasing order */
void my_qsort(struct tnode *v[], int left, int right) {
    int i, last;
    void swap(struct tnode *v[], int, int);

    if (left >= right) /* do nothing if array contains */
        return; /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (v[i]->count > v[left]->count)
            swap(v, ++last, i);
    swap(v, left, last);
    my_qsort(v, left, last-1);
    my_qsort(v, last+1, right);
}

void swap(struct tnode *v[], int i, int j) {
    struct tnode *temp = v[i];

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* treeprint: decreasing order of frequency print */
void treeprint(struct tnode *v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%4d %s\n", v[i]->count, v[i]->word);
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* get a (possibly pushed-back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
