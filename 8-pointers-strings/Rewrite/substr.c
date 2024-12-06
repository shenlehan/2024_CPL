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
    char *p = s;
    while (p < s + strlen(s) - 1) {
        char *tmp = strstr(p, t);
        if (tmp == NULL) {
            break;
        }
        p = tmp + 1;
        printf("%ld ", tmp - s);
    }
    return 0;
}