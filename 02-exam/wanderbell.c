#include <stdio.h>
#define N 3005

const int dir[4][2] = {
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}
};

int r, c, ans;
char map[N][N];

int in(int x, int y) {
    return x >= 1 && x <= r && y >= 1 && y <= c;
}

int main() {
    scanf("%d %d", &r, &c);
    getchar();
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            map[i][j] = getchar();
        }
        getchar();
    }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (map[i][j] != '.') {
                int ok = 0;
                if (map[i][j] == 'R') {
                    for (int k = j + 1; k <= c; ++k) {
                        if (map[i][k] != '.') {
                            ok = 1;
                            break;
                        }
                    }
                } else if (map[i][j] == 'L') {
                    for (int k = j - 1; k >= 1; --k) {
                        if (map[i][k] != '.') {
                            ok = 1;
                            break;
                        }
                    }
                } else if (map[i][j] == 'U') {
                    for (int k = i - 1; k >= 1; --k) {
                        if (map[k][j] != '.') {
                            ok = 1;
                            break;
                        }
                    }                    
                } else if (map[i][j] == 'D'){
                    for (int k = i + 1; k <= r; ++k) {
                        if (map[k][j] != '.') {
                            ok = 1;
                            break;
                        }
                    }                      
                }
                if (ok) {
                    continue;
                }
                for (int t = 0; t < 4; ++t) {
                    int tx = i, ty = j;
                    while (in(tx, ty)) {
                        tx += dir[t][0],
                        ty += dir[t][1];
                        if (!in(tx, ty)) {
                            continue;
                        }
                        if (map[tx][ty] != '.') {
                            // printf("tx ty: %d %d\n", tx, ty);
                            ok = 1;
                            break;
                        }
                    }
                    if (ok) {
                        // printf("%d %d\n", i, j);
                        ++ans;
                        break;
                    }
                }
                if (!ok) {
                    puts("-1");
                    return 0;
                }
            }
        }
    }
    printf("%d", ans);

    return 0;
}