#include <stdio.h>

char map[55][55];
int n;

int dir[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}, {1, 1}
};

int main() {
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            map[i][j] = getchar();     
        }
        getchar();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (map[i][j] == '*') {
                continue;
            }
            map[i][j] = '0';
            int tx, ty;
            for (int k = 0; k < 8; ++k) {
                tx = i + dir[k][0], ty = j + dir[k][1];
                if (tx >= 0 && tx < n && ty >= 0 && ty < n) {
                    if (map[tx][ty] == '*') {
                        ++map[i][j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            putchar(map[i][j]);
        }
        puts("");
    }

    return 0;
}