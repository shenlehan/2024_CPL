#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

char str[1000005];
char delimeter[5];
char s[105][105];
int tot;

int cmp(const void *s1, const void *s2) {
    char *t1 = (char *)s1, *t2 = (char *)s2;
    return strcmp(t1, t2);
}

int main() {
    scanf("%s %s", str, delimeter);
    char *p = strtok(str, delimeter);
    while (p != NULL) {
        // s[tot] = calloc(105, sizeof(char));
        strcpy(s[tot++], p);
        p = strtok(NULL, delimeter);
    }
    qsort(s, tot, sizeof(char) * 105, cmp);
    for (int i = 0; i < tot; ++i) {
        printf("%s\n", s[i]);
    }
    return 0;
}