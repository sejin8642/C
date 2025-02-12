/* Rewrite the program cat from Chapter 7 using read, write, open, 
   and close instead of their standard library equivalents. Perform 
   experiments to determine the relative speeds of the two versions. */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> /* for open */
#include <unistd.h> /* for read, write, and close */

void filecopy(int f1, int f2, char buf[]);

/* cat: copy f1 to STDOUT */
int main(int argc, char *argv[]) {
    int f1, n;
    char buf[BUFSIZ]; // BUFSIZ is from stdio.h

    if (argc == 1)
        filecopy(STDIN_FILENO, STDOUT_FILENO, buf);
    else
        while(--argc > 0)
            if ((f1 = open(*++argv, O_RDONLY, 0)) == -1) {
                printf("cat: can't open %s\n", *argv);
                return 1;
            } 
            else {
                filecopy(f1, STDOUT_FILENO, buf);
                close(f1);
            }

    return 0;
}

void filecopy(int f1, int f2, char buf[]){
    int n;

    while ((n = read(f1, buf, BUFSIZ)) > 0)
        write(f2, buf, n);
}
