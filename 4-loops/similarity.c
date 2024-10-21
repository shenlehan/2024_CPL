#include <stdio.h>

int a[105][105], n, m, tot;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            scanf("%d", &x);
            if (x == a[i][j]) {
                ++tot;
            }
        }
    }

    printf("%.2f\n", 100.0 * tot / (n * m));

    return 0;
}