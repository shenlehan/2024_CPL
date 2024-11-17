#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 805
#define max(x, y) ((x) > (y) ? (x) : (y))

int m, n, d;
long long val[N][N], f[N][N], ans, ansN;

int main() {
    scanf("%d %d %d", &n, &m, &d);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%lld", &val[i + d][j + d]);
        }
    }

    // f[1][1]
    for (int step = 0; step <= d; ++step) {
        for (int k = 0; k <= step; ++k) {
            f[1 + d][1 + d] += val[1 + k + d][1 + step - k + d];
        }
    }

    // calc the first line solely
    // for (int j = 1; j <= m; ++j) {
    //     for (int step = 0; step <= d; ++step) {
    //         for (int k = 0; k <= step; ++k) {
    //             f[1 + d][j + d] += val[1 + k + d][j + step - k + d];
    //             f[1 + d][j + d] += val[1 + k + d][j - step + k + d];
    //         }
    //         f[1 + d][j + d] -= val[1 + step + d][j + d];
    //     }        
    // }
    // printf("f[1][1]: %lld\n", f[1 + d][1 + d]);


    for (int i = 1; i <= n; ++i) {
        if (i % 2) { // odd
            // j = 1
            if(i != 1) {
                f[i + d][1 + d] = f[i - 1 + d][1 + d];

                for (int k = 0; k <= d; ++k) {
                    f[i + d][1 + d] -= val[i - 1 - k + d][1 + d - k + d];
                }
                for (int k = 0; k <= d; ++k) {
                    f[i + d][1 + d] += val[i + k + d][1 + d - k + d];
                }
            }

            for (int j = 2; j <= m; ++j) {
                f[i + d][j + d] = f[i + d][j - 1 + d];
                for (int k = 0; k <= d; ++k) {
                    f[i + d][j + d] -= val[i - k + d][j - 1 - (d - k) + d];
                }
                for (int k = 0; k <= d; ++k) {
                    f[i + d][j + d] -= val[i + k + d][j - 1 - (d - k) + d];
                }
                f[i + d][j + d] += val[i + d][j - 1 - d + d];

                for (int k = 0; k <= d; ++k) {
                    f[i + d][j + d] += val[i - k + d][j + (d - k) + d];
                }
                for (int k = 0; k <= d; ++k) {
                    f[i + d][j + d] += val[i + k + d][j + (d - k) + d];
                }               
                f[i + d][j + d] -= val[i + d][j + d + d];
            }
        } else {
            // j = 1
            f[i + d][m + d] = f[i - 1 + d][m + d];
            for (int k = 0; k <= d; ++k) {
                f[i + d][m + d] -= val[i - 1 - k + d][m - (d - k) + d];
            }
            for (int k = 0; k <= d; ++k) {
                f[i + d][m + d] += val[i + k + d][m - (d - k) + d];
            }

            for (int j = m - 1; j >= 1; --j) {
                f[i + d][j + d] = f[i + d][j + 1 + d];
                for (int k = 0; k <= d; ++k) {
                    f[i + d][j + d] -= val[i - k + d][j + 1 + (d - k) + d];
                }
                for (int k = 0; k <= d; ++k) {
                    f[i + d][j + d] -= val[i + k + d][j + 1 + (d - k) + d];
                }
                f[i + d][j + d] += val[i + d][j + 1 + d + d];

                for (int k = 0; k <= d; ++k) {
                    f[i + d][j + d] += val[i - k + d][j - (d - k) + d];
                }
                for (int k = 0; k <= d; ++k) {
                    f[i + d][j + d] += val[i + k + d][j - (d - k) + d];
                }               
                f[i + d][j + d] -= val[i + d][j - d + d];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            printf("%lld ", f[i + d][j + d]);
        }
        puts("");
    }    

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         ans = max(ans, f[i + d][j + d]);
    //     }
    // }

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         if (ans == f[i + d][j + d]) {
    //             ++ansN;
    //         }
    //     }
    // }
    // printf("%lld %lld\n", ans, ansN);
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         if (ans == f[i + d][j + d]) {
    //             printf("%d %d\n", i, j);
    //         }
    //     }
    // }

    return 0;
}