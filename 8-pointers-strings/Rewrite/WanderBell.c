#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 1005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define min(x, y) ((x) < (y) ? (x) : (y))
#define ll long long

const int dir[4][2] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

int r, c, ans;
char **map;

int in(int x, int y) {
    return 0 <= x && x < r && 0 <= y && y < c;
}

int main() {
    scanf("%d %d", &r, &c);
    map = calloc(1, c * sizeof(char));
    for (int i = 0; i < r; ++i) {
        map[i] = calloc(1, sizeof(char) * c);
    }
    
    getchar();
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            map[i][j] = getchar();
        }
        getchar();
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (map[i][j] == '.') continue;
            int ok = 0;
            if (map[i][j] == 'L') {
                for (int k = 1; j - k >= 0; ++k) {
                    if (map[i][j - k] != '.') {
                        ok = 1;
                        break;
                    }
                }
                if (ok) {
                    continue;
                }
            } else if (map[i][j] == 'R') {
                for (int k = 1; j + k < c; ++k) {
                    if (map[i][j + k] != '.') {
                        ok = 1;
                        break;
                    }
                }
                if (ok) {
                    continue;
                }                
            } else if (map[i][j] == 'U') {
                for (int k = 1; i - k >= 0; ++k) {
                    if (map[i - k][j] != '.') {
                        // log("");
                        ok = 1;
                        break;
                    }
                }
                if (ok) {
                    continue;
                }
            } else {
                for (int k = 1; i + k < r; ++k) {
                    if (map[i + k][j] != '.') {
                        ok = 1;
                        break;
                    }
                }
                if (ok) {
                    continue;
                }                
            }


            for (int k = 0; k < 4; ++k) {
                for (int s = 1; in(i + s * dir[k][0], j + s * dir[k][1]); ++s) {
                    if (map[i + s * dir[k][0]][j + s * dir[k][1]] != '.') {
                        // log("i = %d, j = %d", i + s * dir[k][0], j + s * dir[k][1]);
                        ok = 1;
                        break;
                    }
                }
                if (ok) {
                    break;
                }
            }
            if (!ok) {
                puts("-1");
                return 0;
            }
            ++ans;
        }
    }    
    printf("%d", ans);
    return 0;
}