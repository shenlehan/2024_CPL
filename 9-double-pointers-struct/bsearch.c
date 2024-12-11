#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int a[1000005], n, q, x;

int cmp(const void *a, const void *b) {
    int *x = (int*)a, *y = (int*)b;
    return (*x > *y) - (*x < *y);
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    
    while (q--) {
        scanf("%d", &x);
        int *pos = bsearch(&x, a, n, sizeof(int), cmp);
        if (pos == NULL) {
            printf("-1\n");
        } else {
            printf("%lld\n", pos - a);
        }
    }

    return 0;
}