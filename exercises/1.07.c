#include <stdio.h>

int main () {
    // if you do not put \n at the end of the printf, % will be added to the end 
    // of the output. % is from the terminal or shell, not from the program.
    printf("%d\n", EOF); 

    return 0;
}
