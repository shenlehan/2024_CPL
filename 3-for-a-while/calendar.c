#include <stdio.h>

int m, n;

int main() {
    scanf("%d %d", &m, &n);
    
    --n;
    if (n == 0)
        n = 7;

    if (n != 1)
        for (int i = 1; i <= n - 1; ++i) {
            printf("    ");
        }
    
    for (int i = 1; i <= m; ++i) {
        printf("%2d  ", i);
        if ((i + n - 1) % 7 == 0)
            puts("");
    }

    return 0;
}