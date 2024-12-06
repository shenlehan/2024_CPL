#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

char *buf;

int main() {
    buf = calloc(1, 1005 * sizeof(char));
    scanf("%s", buf);

    for (char *p = buf; *p; ++p) {
        if (p == buf) {
            putchar(toupper(*p));
        } else {
            if (isupper(*p)) {
                putchar(' ');
                putchar(tolower(*p));
            } else {
                putchar(*p);
            }
        }
    }

    free(buf);
    return 0;
}