#include <stdio.h>
#define N 105

int m, n, p, a[105][105], b[105][105], c[105][105];

int main() {
    scanf("%d %d %d", &m, &n, &p);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= p; ++j) {
            scanf("%d", &b[i][j]);
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= p; ++j) {
            for (int k = 1; k <= n; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= p; ++j) {
            printf("%d ", c[i][j]);
        }
        puts("");
    }

    return 0;
}