#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int n, m, d;
int val[605][605], f[605][605];
int ans = INT_MIN;
int p[1000005][2], tot;

int in(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

int main() {
    scanf("%d %d %d", &n, &m, &d);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &val[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        // f[i][1]
        for (int s = 0; s <= d; ++s) {
            for (int k = 0; k <= s; ++k) {
                if (in(i - k, 1 + s - k)) {
                    f[i][1] += val[i - k][1 + s - k];
                }
                if (in(i + k, 1 + s - k)) {
                    f[i][1] += val[i + k][1 + s - k];
                }
            }
            if (in(i, 1 + s)) {
                f[i][1] -= val[i][1 + s];
            }
        }
        ans = max(ans, f[i][1]);

        for (int j = 2; j <= m; ++j) {
            f[i][j] = f[i][j - 1];
            for (int k = 0; k <= d; ++k) {
                if (in(i - k, j - 1 - (d - k)))    
                    f[i][j] -= val[i - k][j - 1 - (d - k)];
                if (in(i + k, j - 1 - (d - k)))    
                    f[i][j] -= val[i + k][j - 1 - (d - k)];
            }
            if (in(i, j - 1 - d))
                f[i][j] += val[i][j - 1 - d];

            for (int k = 0; k <= d; ++k) {
                if (in(i - k, j + (d - k)))    
                    f[i][j] += val[i - k][j + (d - k)];
                if (in(i + k, j + (d - k)))    
                    f[i][j] += val[i + k][j + (d - k)];
            }
            if (in(i, j + d))
                f[i][j] -= val[i][j + d];

            ans = max(ans, f[i][j]);
        }

    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (f[i][j] == ans) {
                p[++tot][0] = i,
                p[tot][1] = j;
            }
        }
    }

    printf("%d %d\n", ans, tot);
    for (int i = 1; i <= tot; ++i) {
        printf("%d %d\n", p[i][0], p[i][1]);
    }

    return 0;
}