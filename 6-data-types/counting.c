#pragma GCC optimize(2)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 105
#define max(x, y) ((x) > (y) ? (x) : (y))

char map[N][N];
int r, c, ans;

void search(int x, int y) {
    for (int len = 1; len <= max(r, c); ++len) {

        int fail = 0;
        for (int step = 0; step < len; ++step) {
            if (x + step >= r || y - step < 0 || y + 1 + step >= c) {
                fail = 1;
                break;
            }
            if (map[x + step][y - step] == '/' && map[x + step][y + 1 + step] == '\\') {
                continue;
            } else {
                fail = 1;
                break;
            }
        }
        if (fail) {
            continue;
        }
        for (int step = 0; step < len; ++step) {
            if (x + len + step >= r) {
                fail = 1;
                break;
            }
            if (map[x + len + step][y - len + 1 + step] == '\\' && map[x + len + step][y + len - step] == '/') {
                continue;
            } else {
                fail = 1;
                break;
            }
        }
        if (!fail) {
            ++ans;
        }
    }
}

int main() {
    scanf("%d %d", &r, &c);
    getchar();
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            map[i][j] = getchar();
        }
        getchar();
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j + 1 < c; ++j) {
            if (map[i][j] == '/' && map[i][j + 1] == '\\') {
                search(i, j);
            }
        }
    }
    printf("%d", ans);

    return 0;
}