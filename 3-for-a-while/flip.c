#include <stdio.h>
#include <math.h>

int a[2005], n;

int main() {
    scanf("%d", &n);
#if 0
    for (int i = 1; i <= n; ++5i) {
        for (int j = 1; j * i <= n; ++j) {
            a[i * j] ^= 1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (a[i]) {
            printf("%d ", i);
        }
    }
#endif

    for (int i = 1; i * i <= n; ++i) {
        printf("%d ", i * i);
    }

    return 0;
}