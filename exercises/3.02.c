#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

/* Write a function escape(s,t) that converts characters like newline 
   and tab into visible escape sequences like \n and \t as it copies 
   the string t to s. Use a switch. Write a function for the other 
   direction as well, converting escape sequences into the real 
   characters. */

int get_line(char line[], int maxline);
void escape(char s[], char t[]);

int main() {
    char line[MAXLINE];     /* current input line */
    char output[MAXLINE];   /* changed string line */

    // from escape sequence to characters
    while (get_line(line, MAXLINE) > 0) {
        escape(output, line);
        printf("%s\n", output);
    }

    return 0;
}

/* getline: read a line into s, return length */
int get_line(char s[], int lim) {
    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

void escape(char s[], char t[]){
    int i = 0;

    while (t[i] != '\0'){
        switch (t[i]){
            case '\n':
                s[i++] = '\\';
                s[i] = 'n';
                break;
            case '\t':
                s[i++] = '\\';
                s[i] = 't';
                break;
            case '\r':
                s[i++] = '\\';
                s[i] = 'r';
                break;
            case '\b':
                s[i++] = '\\';
                s[i] = 'b';
                break;
            case '\f':
                s[i++] = '\\';
                s[i] = 'f';
                break;
            case '\\':
                s[i++] = '\\';
                s[i] = '\\';
                break;
            case '\'':
                s[i++] = '\\';
                s[i] = '\'';
                break;
            case '\"':
                s[i++] = '\\';
                s[i] = '\"';
                break;
            case '\a':
                s[i++] = '\\';
                s[i] = 'a';
                break;
            case '\v':
                s[i++] = '\\';
                s[i] = 'v';
                break;
            default:
                s[i] = t[i];
                break;
        }
        ++i;
    }
}

