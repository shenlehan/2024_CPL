#include <stdio.h>

int vis[55][55];
char map[55][55];
int n, m, x, y, ans;

int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main() {
    scanf("%d %d %d %d", &n, &m, &x, &y);
    getchar();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            map[i][j] = getchar();
            if (map[i][j] == '#') {
                ++ans;
            }         
        }
        getchar();
    }

    printf("%d\n", ans);

    for (int i = 0; i < ans; ++i) {
        vis[x][y] = 1;
        printf("%d %d\n", x, y);
        int tx, ty;
        for (int j = 0; j < 4; ++j) {
            tx = x + dir[j][0], ty = y + dir[j][1];
            if (tx <= n && ty <= m) {
                if (!vis[tx][ty] && map[tx][ty] == '#') {
                    x = tx, y = ty;
                    break;
                }
            }
        }
    }

    return 0;
}