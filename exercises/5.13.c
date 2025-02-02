#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for atoi
#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines, char *allocp);
void writelines(char *lineptr[], int nlines);

/* tail -n program */
int main(int argc, char *argv[]) {
    int nlines, n; /* number of lines to be printed */
    char allocbuf[MAXLINES*MAXLEN]; /* storage for lines */

    if ((nlines = readlines(lineptr, MAXLINES, allocbuf)) >= 0) {
        if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'n' && (n = atoi(argv[2])))
            if (n < 0) // terminate the program if n is less than 0
                return;
            nlines = (n < nlines) ? n: nlines;
        writelines(lineptr, nlines);
        return 0;
    } 
    else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *allocp) {
    int len, nlines;
    char line[MAXLEN];
    int get_line(char *, int);

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(allocp, line); /* copy the read line into allocbuf */
            allocp += len;
            lineptr[nlines++] = allocp;
        }

    return nlines;
}

/* get_line: read a line into s, return length */
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", lineptr[nlines]);
}
