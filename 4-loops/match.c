#include <stdio.h>

int n, m, a[505][505];
int posx1[505 * 505 / 2], posy1[505 * 505 / 2], posx2[505 * 505 / 2], posy2[505 * 505 / 2];
int vis[505 * 505 / 2];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            if (!vis[a[i][j]]) {
                vis[a[i][j]] = 1;
                posx1[a[i][j]] = i, posy1[a[i][j]] = j;
            } else {
                posx2[a[i][j]] = i, posy2[a[i][j]] = j;
            }
        }
    }
    
    for (int num = 1; num <= n * m / 2; ++num) {
        // find num pos
        int x1 = posx1[num], y1 = posy1[num], x2 = posx2[num], y2 = posy2[num];
        // go left
        int tx = x1, ty = y1 - 1;
        int fail = 0;
        for (; ty >= 0; --ty) {
            if (a[tx][ty]) {
                fail = 1;
                break;
            }
        }
        if (!fail) {
            tx = x2;
            fail = 0;
            for (; ty <= y2 - 1; ++ty) {
                if (a[tx][ty]) {
                    fail = 1;
                    break;
                }
            }
        }

        if (!fail) {
            a[x1][y1] = a[x2][y2] = 0;
            printf("%d ", num);
            continue;
        }

        // go right
        tx = x1, ty = y1 + 1;
        fail = 0;
        for (; ty <= m + 1; ++ty) {
            if (a[tx][ty]) {
                fail = 1;
                break;
            }
        }
        if (!fail) {
            tx = x2;
            fail = 0;
            for (; ty >= y2 + 1; --ty) {
                if (a[tx][ty]) {
                    fail = 1;
                    break;
                }
            }
        }

        if (!fail) {
            a[x1][y1] = a[x2][y2] = 0;
            printf("%d ", num);
            continue;   
        }  

        // go up
        tx = x1 - 1, ty = y1;
        fail = 0;
        for (; tx >= 0; --tx) {
            if (a[tx][ty]) {
                fail = 1;
                break;
            }
        }
        if (!fail) {
            ty = y2;
            fail = 0;
            for (; tx <= x2 - 1; ++tx) {
                if (a[tx][ty]) {
                    fail = 1;
                    break;
                }
            }
        }

        if (!fail) {
            a[x1][y1] = a[x2][y2] = 0;
            printf("%d ", num);
            continue;
        }

      

        // go down
        tx = x1 + 1, ty = y1;
        fail = 0;
        for (; tx <= n + 1; ++tx) {
            if (a[tx][ty]) {
                fail = 1;
                break;
            }
        }
        if (!fail) {
            ty = y2;
            fail = 0;
            for (; tx >= x2 + 1; --tx) {
                if (a[tx][ty]) {
                    fail = 1;
                    break;
                }
            }
        }

        if (!fail) {
            a[x1][y1] = a[x2][y2] = 0;
            printf("%d ", num);
            continue;
        }
    }

    return 0;
}