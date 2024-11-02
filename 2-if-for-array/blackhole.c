#include <stdio.h>
#include <math.h>

int ans, d[5], n, n1;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void sort1(int *a) { // min
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
            }
        }
    }
}

void sort2(int *a) { // max
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            if (a[i] < a[j]) {
                swap(&a[i], &a[j]);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    while (n != 495) {
        n1 = n;
        d[0] = n / 100, n %= 100;
        d[1] = n / 10, n %= 10;
        d[2] = n;
        sort1(d);
        int x1 = 100 * d[0] + 10 * d[1] + d[2];
        sort2(d);
        int x2 = 100 * d[0] + 10 * d[1] + d[2];
        n = x2 - x1;
        swap(&n, &n1);
        if (n > n1) {
            ans += n - n1;
        }
        n = n1;
    }
    printf("%d", ans);
    return 0;
}