#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

/*  Write a function reverse(s) that reverses the character string s. Use it to
    write a program that reverses its input a line at a time. */

int get_line(char line[], int maxline);
void reverse(char line[]);

int main() {
    char line[MAXLINE]; /* current input line */

    while (get_line(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s\n", line);
    }

    return 0;
}

/* getline: read a line into s, return length */
int get_line(char s[], int lim) {
    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF && c !='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

void reverse(char s[]){
    int i, j, temp;
    j = 0;

    for (i = 0; s[i] != '\n'; ++i);

    --i;
    while (j < i) {
       temp = s[j];
       s[j] = s[i];
       s[i] = temp;
       --i;
       ++j;
    }
}
