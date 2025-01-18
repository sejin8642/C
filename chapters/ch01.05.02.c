#include <stdio.h>
/* count characters in input; 2nd version */

int main() {
    double nc; 

    // you can declare nc inside the for-loop parentheses, but it will not exist outside of 
    // the for-loop, i.e., it is local to the loop and only exists for the duration of the loop.
    for (nc = 0; getchar() != EOF; ++nc);

    // you will not see the print output until you SIGNAL EOF
    // on MacOS, EOF signal is Ctrl + D. Also, notice that there is a space before \n in printf.
    // On the terminal, if the output number is a single digit, a letter D is added.
    printf("%.0f \n", nc);

    return 0;
}
