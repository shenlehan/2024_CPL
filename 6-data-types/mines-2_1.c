#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define N 605

const int dir[6][3] = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1}
};

int n, p[3], tot, fail1, fail2;
int wp[125][3], cnt;
char map[N][N][N];

bool in(int x, int y, int z) {
    if (x <= 0 || x > n) return 0;
    if (y <= 0 || y > n) return 0;
    if (z <= 0 || z > n) return 0;
    return 1;
}

int main() {
    scanf("%d", &n);
    getchar();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {   
            for (int k = 1; k <= n; ++k) {
                map[i][j][k] = getchar();
                if (map[i][j][k] == '?') {
                    p[0] = i, p[1] = j, p[2] = k;
                }
            }
        }
    }

    // is not mine
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (isdigit(map[i][j][k]) || map[i][j][k] == '?') {
                    tot = 0;
                    for (int t = 0; t < 6; ++t) {
                        if (!in(i + dir[t][0], j + dir[t][1], k + dir[t][2]))
                            continue;
                        if (map[i + dir[t][0]][j + dir[t][1]][k + dir[t][2]] == '*')
                            ++tot;
                    }
                    if (isdigit(map[i][j][k]) && tot != map[i][j][k] - '0') {
                        fail1 = 1;
                        break;
                    } else {
                        map[i][j][k] = '0' + tot;
                    }
                }
            }
        }
    }   

    if (!fail1) {
        puts("valid");
        putchar(map[p[0]][p[1]][p[2]]);
        return 0;
    }

    // is mine
    map[p[0]][p[1]][p[2]] = '*';
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (isdigit(map[i][j][k])) {
                    tot = 0;
                    for (int t = 0; t < 6; ++t) {
                        if (!in(i + dir[t][0], j + dir[t][1], k + dir[t][2]))
                            continue;
                        if (map[i + dir[t][0]][j + dir[t][1]][k + dir[t][2]] == '*')
                            ++tot;
                    }
                    if (tot != map[i][j][k] - '0') {
                        fail2 = 1;
                        wp[cnt][0] = i,
                        wp[cnt][1] = j,
                        wp[cnt][2] = k;
                        ++cnt;
                    }
                }
            }
        }
    }
    if (fail2) {
        puts("invalid");
        for (int i = 0; i < cnt; ++i) {
            printf("%d %d %d\n", wp[i][0], wp[i][1], wp[i][2]);
        }
    } else {
        puts("valid");
        putchar('*');
    }

    return 0;
}