#include <stdio.h>

int a[1000000 + 5], n, k, pivot, pos;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    
    pos = k;
    pivot = a[k];

    int l = 1, r = n;
    while (l != r) {
        for (; l < r && a[l] < pivot; ++l);
        for (; l < r && a[r] >= pivot; --r);

        if (l != r) {
            swap(&a[l], &a[r]);
            continue;
        }

        for (int i = 1; i <= n; ++i) {
            if (a[i] == pivot) {
                pos = i;
                break;
            }
        }

        if (l == r && a[l] >= a[pos]) {
            swap(&a[l], &a[pos]);
        }

    }

    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);

    return 0;
}