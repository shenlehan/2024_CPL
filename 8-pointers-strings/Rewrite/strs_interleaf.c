#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int T;
char *s1, *s2;
int ds1, ds2, size;

// always remember to judge "i + xxx < strlen(s)"
// this is really critical

void interleaveString(char *s, char *t, int sz) {
    char *s3 = calloc(1, sizeof(char) * (sz + 10)); // bigger
    int ps = 0, pt = 0, len = 0;
    while (ps < strlen(s) && pt < strlen(t) && len < sz - 1) {
        int i, j;
        for (i = 0; i < ds1 && ps + i < strlen(s) && len < sz - 1; ++i) {
            s3[len++] = s[ps + i];
        }
        ps += i;

        for (j = 0; j < ds2 && pt + j < strlen(t) && len < sz - 1; ++j) {
            s3[len++] = t[pt + j];
        }
        pt += j;     
    }
    while (ps < strlen(s) && len < sz - 1) {
        s3[len++] = s[ps++];
    }
    while (pt < strlen(t) && len < sz - 1) {
        s3[len++] = t[pt++];
    }
    s3[len] = '\0';
    puts(s3);
    free(s3);
    return;
}

int main() {
    scanf("%d", &T);
    s1 = calloc(1, sizeof(char) * 1005);
    s2 = calloc(1, sizeof(char) * 1005);
    getchar();
    while (T--) {
        int l1 = 0, l2 = 0;
        char ch;
        while ((ch = getchar()) != ';') {
            s1[l1++] = ch;
        }
        s1[l1] = '\0';
        while ((ch = getchar()) != ';') {
            s2[l2++] = ch;
        }
        s2[l2] = '\0';
        scanf("%d;%d;%d", &ds1, &ds2, &size);
        getchar();
        // printf("s1 = %s, s2 = %s, ds2 = %d, ds2 = %d, size = %d\n", s1, s2, ds1, ds2, size);
        interleaveString(s1, s2, size);
    }
    free(s1);
    free(s2);
    return 0;
}