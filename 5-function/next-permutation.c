#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 2005

int n, m = 1, p[N];

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &p[i]);

    for (int i = n - 1; i >= 1; --i) {
        if (p[i + 1] > p[i])
            break;
        ++m;
    }

    int minv = p[n - m], cur = 0x7fffffff, t;
    for (int i = n - m + 1; i <= n; ++i) {
        if (p[i] > minv && p[i] < cur) {
            cur = p[i];
            t = i;
        }
    }
    swap(&p[n - m], &p[t]);
    for (int i = 1; i <= n - m; ++i)
        printf("%d ", p[i]);
    for (int i = n; i >= n - m + 1; --i)
        printf("%d ", p[i]);

    return 0;
}