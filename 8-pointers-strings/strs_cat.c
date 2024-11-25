#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

int T;
char *s1, *s2;

void mystrcat(char *s, char *t) {
    int ps = 0, lens = strlen(s), lent = strlen(t);
    int maxlen = -1;
    while (ps < lens) {
        int pt = 0, k = ps;
        while (*(s + k) == *(t + pt) && k < lens && pt < lent) {
            ++pt, ++k;
        }

        if (k == lens)
            maxlen = max(maxlen, pt);
        ++ps;
    }
    printf("%s", s);
    if (maxlen == -1) {
        maxlen = 0;
    }
    for (int i = maxlen; i < lent; ++i) {
        putchar(*(t + i));
    }
    puts("");
}

int main() {
    scanf("%d", &T);
    s1 = malloc(2005 * sizeof(char));
    s2 = malloc(2005 * sizeof(char));

    while (T--) {
        scanf("%s %s", s1, s2);
        mystrcat(s1, s2);
    }

    return 0;
}