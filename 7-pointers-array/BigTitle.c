#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char ch;
int t;

int main() {
    while ((ch = getchar()) != EOF) {
        if (!t) {
            putchar(toupper(ch));
            t = 1;
        } else if (ch == ' ') {
            putchar(ch);
            t = 0;
        } else {
            putchar(tolower(ch));
        }
    }
    return 0;
}