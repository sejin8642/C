#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100

/* Extend atof to handle scientific notation */
int main() {
    double sum, atof(char []);
    char line[MAXLINE];
    int get_line(char line[], int max);

    sum = 0;
    while (get_line(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));

    return 0;
}

/* atof: convert string s to double */
double atof(char s[]) {
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++); /* skip white space */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    else 
        return sign * val / power;

    int p, n;
    double e;

    p = (s[i] == '-') ? -1: 1;
    if (p == -1 || s[i] == '+')
        i++;
    for (n = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    for (e = 1.0; 0 < n; n--)
        e *= 10;
    if (p == -1)
        return sign * val / (power * e);
    else
        return sign * val * e / power;
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
