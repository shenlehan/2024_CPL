#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

char *s, *t;

int main() {
    s = calloc(1, sizeof(char) * 100005);
    t = calloc(1, sizeof(char) * 100005);
    scanf("%s %s", s, t);
    for (char *p = s; (p = strstr(p, t)) != NULL; ++p) {
        printf("%lld ", p - s);
    }
    return 0;
}