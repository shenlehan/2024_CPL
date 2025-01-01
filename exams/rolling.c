#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define N 55

int m, n;
int a[N][N], vis[N][N], pos[N];

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int j = 0; j < n; ++j) {
        // log("##############");
        int x = 0, y = j;
        int fail = 0;
        for (int i = 0; i < m; ++i) {
            if (y != 0 && y != n - 1) {
                if ((a[x][y] == 1 && a[x][y + 1] == -1) || (a[x][y] == -1 && a[x][y - 1] == 1)) {
                    fail = 1;
                    break;
                }
            } else if (y == 0) {
                if (a[x][y] == -1) {
                    fail = 1;
                    break;
                }
            } else if (y == n - 1) {
                if (a[x][y] == 1) {
                    fail = 1;
                    break;
                }
            }
            // log("Now at (%d,%d)", x, y);
            y += a[x][y];
            ++x;

        }
        if (!fail) printf("%d ", y);
        else printf("-1 ");
    }

    return 0;
}