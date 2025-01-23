#include <stdio.h>
#define MAXLINES 100000 // maximum input line size

/* Write a program to remove all comments from a C program. 
   Don't forget to handle quoted strings and character constants properly. 
   It was assumed that input code compiles correctly without any error */

// print code without comment 
int main() {
    char lines[MAXLINES]; // code lines without comment
    int c, p, i, MLS, SLS, SS;

    // first iteration of getchar 
    p = getchar();
    lines[0] = p;
    i = 1;

    SS = 0;  // to keep track of in-or-out string state
    MLS = 0; // to keep track of in-or-out multiple line comment state  
    SLS = 0; // to keep track of in-or-out single line comment state  
    while (i < MAXLINES - 1 && (c=getchar()) != EOF){
        // check for string state
        if (c == '"' && p != '\\' && SS == 0 && SLS == 0 && MLS == 0)
            SS = 1;
        else if (c == '"' && SS == 1)
            SS = 0;

        // check for multi line comment state
        if (p == '/' && c == '*' && SS == 0 && SLS == 0) {
            MLS = 1;
            --i;
        }
        if (p == '*' && c == '/' && MLS == 1 && SS == 0 && SLS == 0) {
            MLS = 0;
            c = getchar();
        }

        // check for single line comment state
        if (p == '/' && c == '/' && SS == 0 && MLS == 0) {
            SLS = 1;
            --i;
        }
        if (SLS == 1 && c == '\n')
            SLS = 0;

        // put the character if not in any comment state
        if (SLS == 0 && MLS == 0) {
            lines[i] = c;
            ++i;
        }

        p = c;
    }
    lines[i] = '\0';

    printf("\noutput:\n\n");
    printf("%s", lines);
    return 0;
}
