#include <stdio.h>

#define ASCII_SIZE 128  // Total number of ASCII characters

int main() {
    int c;
    int frequencies[ASCII_SIZE] = {0};

    // Read characters from input and count their frequencies
    printf("Enter text (Ctrl+D to end input on Linux/Mac, Ctrl+Z on Windows):\n");
    while ((c = getchar()) != EOF) {
        if (c >= 0 && c < ASCII_SIZE) {
            frequencies[c]++;
        }
    }

    // Print the histogram
    printf("\nCharacter Frequency Histogram:\n");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequencies[i] > 0) {
            // Print the character (handle non-printable characters for clarity)
            if (i >= 32 && i <= 126) {  // Printable ASCII range
                printf("'%c' | ", i);
            } else {
                printf("'\\x%02X' | ", i);  // Hex representation for non-printables
            }

            // Print the frequency as a bar
            for (int j = 0; j < frequencies[i]; j++) {
                printf("#");
            }
            printf(" (%d)\n", frequencies[i]);  // Show the frequency count
        }
    }

    return 0;
}

