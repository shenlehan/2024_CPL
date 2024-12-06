#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int T;
char *s1, *s2, *ans;

void my_strcat(const char *s, const char *t) {
    for (const char *p = s; *p; ++p) {
        char *tmp = strstr(t, p);
        if (tmp == t) {
            strcpy(ans, s);
            strcat(ans, t + strlen(p));
            printf("%s\n", ans);
            return;
        }
    }

    // handle the null 
    strcpy(ans, s);
    strcat(ans, t);
    printf("%s\n", ans);    
}

int main() {
    scanf("%d", &T);
    s1 = calloc(1, sizeof(char) * 1005);
    s2 = calloc(1, sizeof(char) * 1005);
    ans = calloc(1, sizeof(char) * 2005);
    while (T--) {
        scanf("%s %s", s1, s2);
        my_strcat(s1, s2);
    } 
    return 0;
}