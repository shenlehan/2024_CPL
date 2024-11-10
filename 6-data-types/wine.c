#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 10005

int n, l;

struct wine {
    int v, w;
} a[N];

int cmp(wine x, struct wine y) {
    if (x > y) return 1;
    else if (x == y) return 0;
    else if (x < y) return -1;
}

int main() {
    scanf("%d %d", &n, &l);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i].w);

    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i].v);

    qsort()

    while (l > 0) {

    }

    return 0;
}