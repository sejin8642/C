/* An alternate organization uses getline to read an entire input 
   line; this makes getch and ungetch unnecessary. Revise the 
   calculator to use this approach. */
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define MAXLINE 1000

char line[MAXLINE];
int get_line(char s[], int lim);
int getop(char []);
int lp; /* current line position */
void push(double);
double pop(void);
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];

    while (get_line(line, MAXLINE) > 0){
        lp = 0;
        while ((type = getop(s)) != '\n') {
            switch (type) {
                case NUMBER:
                    push(atof(s));
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("error: zero divisor\n");
                    break;
                default:
                    printf("error: unknown command %s\n", s);
                    break;
            } 
        } 
        printf("\t%.8g\n", pop());
    } 

    return 0;
}

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];

    printf("error: stack empty\n");
    return 0.0;
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((c = line[lp++]) == ' ' || c == '\t');
    s[0] = c;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* not a number */
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = line[lp++]));
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = line[lp++]));
    s[i] = '\0';
    lp--;

    return NUMBER;
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
