#include <stdio.h>

int a[1000005], n;

int main() {
    scanf("%d", &n);
    for (int i = 0, x; i < 2 * n - 1; ++i) {
        scanf("%d", &x);
        a[x]++;
    }
    for (int i = 1; i <= 10 * n; ++i) {
        if (a[i] == 1) {
            printf("%d", i);
        }
    }
    return 0;
}