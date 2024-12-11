#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

const char *delimeter = ";";

int T;
char line[5005], ans[2005];

void interleaveString(const char *s, const char *t, int ds1, int ds2, int size) {
    int pa = 0, lens = strlen(s), lent = strlen(t);
    int ps = 0, pt = 0;

    while (pa < size - 1 && ps < lens && pt < lent) {
        int i = 0;
        for (i = 0; ps < lens && pa < size - 1 && i < ds1; ++i) {
            ans[pa++] = s[ps++];
        }
        

        for (i = 0; pt < lent && pa < size - 1 && i < ds2; ++i) {
            ans[pa++] = t[pt++];
        }  
        pt += i;  
    }

    while (ps < lens && pa < size - 1) ans[pa++] = s[ps++];
    while (pt < lent && pa < size - 1) ans[pa++] = t[pt++];
    ans[pa] = 0;
    printf("%s\n", ans);   
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%s", line);
        char *s1 = strtok(line, delimeter);
        char *s2 = strtok(NULL, delimeter);
        char *_ds1 = strtok(NULL, delimeter);
        char *_ds2 = strtok(NULL, delimeter);
        char *_sz = strtok(NULL, delimeter);
        int ds1 = atoi(_ds1),
            ds2 = atoi(_ds2),
            sz = atoi(_sz);
        interleaveString(s1, s2, ds1, ds2, sz);
    }
    return 0;
}