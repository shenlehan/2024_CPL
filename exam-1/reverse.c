#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *str;
int len;

int main() {
    scanf("%d", &len);
    str = malloc(len + 1);
    scanf("%s", str);

    for (int i = len - 1; i >= 0; --i) {
        if (!isdigit(str[i])) {
            if ('a' <= str[i] && str[i] <= 'z') {
                putchar(str[i] - 'a' + 'A');
            } else {
                putchar(str[i] - 'A' + 'a');
            }
        } else {
            putchar(str[i]);
        }
    }

    return 0;
}