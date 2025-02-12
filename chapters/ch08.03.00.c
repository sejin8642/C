#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> /* for open and creat */
#include <stdarg.h> /* for va_list */
#include <unistd.h> /* for read() and write() */
#define PERMS 0666 /* RW for owner, group, others */

void error(char *, ...);

/* cp: copy f1 to f2 */
int main(int argc, char *argv[]) {
    int f1, f2, n;
    char buf[BUFSIZ]; // BUFSIZ is from stdio.h

    if (argc != 3)
        error("Usage: cp from to");
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
        error("cp: can't open %s", argv[1]);
    if ((f2 = creat(argv[2], PERMS)) == -1) 
        error("cp: can't create %s, mode %03o", argv[2], PERMS);
    while ((n = read(f1, buf, BUFSIZ)) > 0)
        if (write(f2, buf, n) != n)
            error("cp: write error on file %s", argv[2]);
    return 0;
}

/* error: print an error message and die */
void error(char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
