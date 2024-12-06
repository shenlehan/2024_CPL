#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 605
#define max(x, y) ((x) > (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

const int dir[6][3] = {
    {1, 0, 0}, {-1, 0, 0},
    {0, 1, 0}, {0, -1, 0},
    {0, 0, 1}, {0, 0, -1}
};

int n, unk_x, unk_y, unk_z;
int p[1000005][3], tot;
char map[N][N][N];

int in(int x, int y, int z) {
    return 0 <= x && x < n
        && 0 <= y && y < n
        && 0 <= z && z < n;
}

int check(int state) {
    int inv = 0;
    tot = 0;
    if (state == 0) {
        map[unk_x][unk_y][unk_z] = '7';
    } else {
        map[unk_x][unk_y][unk_z] = '*';
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (isdigit(map[i][j][k])){
                    int cnt = 0;
                    for (int t = 0; t < 6; ++t) {
                        int px = i + dir[t][0],
                            py = j + dir[t][1],
                            pz = k + dir[t][2];

                        if (!in(px, py, pz)) continue;
                        if (map[px][py][pz] == '*') ++cnt;
                    }

                    if (cnt != map[i][j][k] - '0' && map[i][j][k] != '7') {
                        inv = 1;
                        p[tot][0] = i,
                        p[tot][1] = j,
                        p[tot][2] = k;
                        ++tot;
                    } else if (map[i][j][k] == '7') {
                        map[i][j][k] = cnt + '0'; // +'0' or -'0'
                    }
                }
            }
        }
    }


    if (state == 0) {
        if (inv) {
            map[unk_x][unk_y][unk_z] = '?';   
            return 0; 
        } else {
            return 1;
        }
    } else {
        if (!inv) {
            return 1;
        } else {
            return 0;
        }
    }

}

int main() {
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                map[i][j][k] = getchar();
                if (map[i][j][k] == '?') {
                    unk_x = i, unk_y = j, unk_z = k;
                }
            }
        }
    }

    if (check(0)) {
        puts("valid");
        putchar(map[unk_x][unk_y][unk_z]);
    } else {
        if (check(1)) {
            puts("valid");
            putchar('*');
        } else {
            puts("invalid");
            for (int i = 0; i < tot; ++i) {
                printf("%d %d %d\n", p[i][0] + 1, p[i][1] + 1, p[i][2] + 1);
            }
        }
    }

    return 0;
}