#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int r, c, ans;
char map[105][105];

int in(int x, int y) {
    return 0 <= x && x < r && 0 <= y && y < c;
}

void search(int x, int y) {
    for (int s = 1; s <= max(r, c); ++s) {
        int f = 0;
        for (int i = 0; i < s; ++i) {
            if (!in(x + i, y - i) || !in(x + i, y + 1 + i)) {
                f = 1;
                break;
            }
            if (map[x + i][y - i] != '/' || map[x + i][y + 1 + i] != '\\') {
                f = 1;
                break;
            }
        }
        if (f) {
            continue;
        }
        for (int i = 0; i < s; ++i) {
            if (!in(x + s + i, y - s + i + 1) || !in(x + s + i, y + 1 + s - 1 - i)) {
                f = 1;
                break;
            }
            if (map[x + s + i][y - s + i + 1] != '\\' || map[x + s + i][y + 1 + s - 1 - i] != '/') {
                f = 1;
                break;
            }            
        }
        if (!f) {
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
        for (int j = 0; j < c; ++j) {
            if (map[i][j] == '/' && map[i][j + 1] == '\\') {
                search(i, j);
            }
        }
    }
    printf("%d", ans);
    return 0;
}