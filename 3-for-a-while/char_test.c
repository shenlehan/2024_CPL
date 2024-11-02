#include <stdio.h>

char s[100];

int main() {
    s[10] = 'z';
    for (int i = 0; i <= 10; ++i)
    //    printf("%c", s[i]);
        putchar(s[i]);
    return 0;
}