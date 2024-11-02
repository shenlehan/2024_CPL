#include <stdio.h>

int n, map[1005][1005];

int main() {
    scanf("%d", &n);
    int lastx = 0, lasty = n >> 1;
    for (int i = 1; i <= n * n; ++i) {
        map[lastx][lasty] = i;
        int tx = lastx - 1, ty = lasty + 1;
        tx = (tx + n) % n, ty = (ty + n) % n;
        if (map[tx][ty]) {
            tx = lastx + 1, ty = lasty;
        }

        lastx = tx, lasty = ty;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", map[i][j]);
        }
        puts("");
    }
    return 0;
}