/* Our version of getword does not properly handle underscores, 
   string constants, comments, or preprocessor control lines. 
   Write a better version. */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100

struct key {
        char *word;
        int count;
} keytab[] = {
    "auto" , 0,
    "break" , 0,
    "case" , 0,
    "char" , 0,
    "const" , 0,
    "continue" , 0,
    "default" , 0,
    "do" , 0,
    "double" , 0,
    "else" , 0,
    "enum" , 0,
    "extern" , 0,
    "float" , 0,
    "for" , 0,
    "goto" , 0,
    "if" , 0,
    "int" , 0,
    "long" , 0,
    "register" , 0,
    "return" , 0,
    "short" , 0,
    "signed" , 0,
    "sizeof" , 0,
    "static" , 0,
    "struct" , 0,
    "switch" , 0,
    "typedef" , 0,
    "union" , 0,
    "unsigned" , 0,
    "void" , 0,
    "volatile" , 0,
    "while" , 0,
};

#define NKEYS (sizeof keytab / sizeof(keytab[0]))

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main() {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                    keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* getword: get next word or character from input, handling underscores, strings, comments, and preprocessor directives */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    // Skip whitespace
    while (isspace(c = getch())) {
        ;
    }

    // Check for comments or preprocessor directives
    if (c == '/') {
        int next_c = getch();
        if (next_c == '*') {
            // Skip block comment
            while (! (c == '*' && next_c == '/')) {
                c = next_c;
                next_c = getch();
            }
            c = next_c;
        } else if (next_c == '/') {
            // Skip line comment
            while (c != '\n' && c != EOF) {
                c = getch();
            }
        } else {
            ungetch(next_c);
        }
    } else if (c == '#') {
        // Skip preprocessor directive
        while (c != '\n' && c != EOF) {
            c = getch();
        }
    }

    // Check for string constant
    if (c == '"') {
        // Read string constant
        for (; lim > 1; w++) {
            if ((*w = getch()) == '"') {
                // End of string
                break;
            }
            if (*w == '\\') {
                // Handle escape characters (e.g., \" or \\)
                *++w = getch();
            }
        }
        *w = '\0';
        return c;
    }

    // Read identifier with underscores
    if (isalpha(c) || c == '_') {
        *w++ = c;
        for (; --lim > 0; w++) {
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }
        }
        *w = '\0';
        return c;
    }

    *w = '\0';
    return c;
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
