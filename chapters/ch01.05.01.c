#include <stdio.h>
/* copy input to output; 2nd version */

int main(){
    int c;
    // if there is only one line instruction for while, if, or for-loop, 
    // you do not need { } to enclose the instruction
    while ((c = getchar()) != EOF) putchar(c);
    // getchar is a blocking function that does not return control to the program until 
    // it has completed its task. When a blocking function is called, the program execution 
    // pauses at that point, and no further code is executed until the function completes.
    // in this context, blocking means that the function causes the program to wait for 
    // some external event or resource to be available before it proceeds.

    return 0;
}
