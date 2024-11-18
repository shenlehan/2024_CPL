#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define N 605
#define log(f, args...) do { printf("%s %d ", __FUNCTION__, __LINE__); printf(f, ##args); puts(""); } while (0)
#define max(x, y) ((x) > (y) ? (x) : (y))

int n, m, d;
long long val[N][N], f[N][N];
long long ans = INT_MIN, ansN;
int p[N][2];

bool in(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int main() {
    scanf("%d %d %d", &n, &m, &d);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%lld", &val[i][j]);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j == 1) {
                for (int step = 0; step <= d; ++step) {
                    for (int k = 0; k <= step; ++k) {
                        if (in(i + (step - k), j + k)) {
                            f[i][1] += val[i + (step - k)][1 + k];
                            // log("now visiting: %d", val[i + (step - k)][1 + k]);
                        }
                        if (in(i - (step - k), j + k)) {
                            f[i][1] += val[i - (step - k)][1 + k];
                            // log("now visiting: %d", val[i - (step - k)][1 + k]);
                        }
                    }
                    if (in(i, 1 + step)) {
                        f[i][1] -= val[i][j + step];
                    }
                }
                // log("f[%d][1] = %d", i, f[i][1]);                
            } else {
                f[i][j] = f[i][j - 1];
                for (int k = 0; k <= d; ++k) {
                    if (in(i - k, j - 1 - (d - k))) {
                        f[i][j] -= val[i - k][j - 1 - (d - k)];
                    }
                    if (in(i + k, j - 1 - (d - k))) {
                        f[i][j] -= val[i + k][j - 1 - (d - k)];
                    }
                    if (in(i - k, j + (d - k))) {
                        f[i][j] += val[i - k][j + (d - k)];
                    }
                    if (in(i + k, j + (d - k))) {
                        f[i][j] += val[i + k][j + (d - k)];
                    }
                }
                if (in(i, j - 1 - d)) {
                    f[i][j] += val[i][j - 1 - d];
                }
                if (in(i, j + d)) {
                    f[i][j] -= val[i][j + d];
                }
            }
            ans = max(ans, f[i][j]); 
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (f[i][j] == ans) {
                ++ansN;
                p[ansN][0] = i, p[ansN][1] = j;
            }
        }
    }

    printf("%lld %lld\n", ans, ansN);
    for (int i = 1; i <= ansN; ++i) {
        printf("%d %d\n", p[i][0], p[i][1]);
    }

    return 0;
}