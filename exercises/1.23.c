#include <stdio.h>
#define MAXLINES 100000 /* maximum input line size */

/* Write a program to remove all comments from a C program. 
   Don't forget to handle quoted strings and character constants properly. 
   It was assumed that string does not contain comment delimiters */

/* print code without comment */
int main() {
    char lines[MAXLINES]; /* code lines without comment */
    int c, p, i, state;

    i = 0;
    state = 0; /* to keep track of in-or-out comment state */ 
    while (i < MAXLINES - 1 && (c=getchar()) != EOF){
        if (p == '/' && c == '*') {
            state = 1;
            --i;
        }
        if (p == '*' && c == '/') {
            state = 0;
            c = getchar();
        }
        if (state == 0) {
            lines[i] = c;
            ++i;
        }

        p = c;
    }
    ++i;
    lines[i] = '\0';

    printf("%s", lines);
    return 0;
}
