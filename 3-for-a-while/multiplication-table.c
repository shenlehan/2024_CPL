#include <stdio.h>

int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf("%dx%d=%d ", j, i, i * j);
        }
        puts("");
    }
    return 0;
}