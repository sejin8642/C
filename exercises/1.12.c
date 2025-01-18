#include <stdio.h>
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */
/* Write a program that prints its input one word per line */

int main() {
    int c, state;
    state = IN;

    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\n' && c != '\t') {
            putchar(c);
            state = IN;
        }
        else if (state == IN) {
            state = OUT;
            putchar('\n');
        }
    }

    return 0;
}
