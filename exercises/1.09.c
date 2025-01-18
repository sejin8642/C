#include <stdio.h>
/* replace multiple blanks in input into a single blank */

int main() {
    int c, b;
    b = 0;

    while ((c = getchar()) != EOF) {
        if (c != b) putchar(c);
        if (c == b) 
            if (c != ' ') 
                putchar(c);
        b = c;
    }

    return 0;
}
