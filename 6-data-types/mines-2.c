#include <stdio.h>
#include <ctype.h>
#define N 605

const int dir[10][10] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {-1, 0, 0},
    {0, -1, 0},
    {0, 0, -1}
};

char map[N][N][N];
int n;
char invalid[2] = {0, 0};
char uncert[5] = {0, 0, 0}, mines[N][N][N];
int invalid_pos[121][5], cnt;
// mines[i][j][k] = * -> around (i, j, k) has * mines

int in(int x, int y, int z) {
    if (x <= 0 || x > n) return 0;
    if (y <= 0 || y > n) return 0;
    if (z <= 0 || z > n) return 0;
    return 1;
}
    

void check(int p) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (isdigit(map[i][j][k])) {
                    if (mines[i][j][k] != map[i][j][k] - '0') {
                        // if (p == 1) {
                        //     printf("%d %d %d %d\n", __LINE__, i, j, k);
                        //     printf("%d %d %d\n", __LINE__, mines[i][j][k], map[i][j][k] - '0');
                        // }

                        invalid[p] = 1;
                        if (p == 1) {
                            cnt++;
                            invalid_pos[cnt][0] = i,
                            invalid_pos[cnt][1] = j,
                            invalid_pos[cnt][2] = k;
                        }
                    }
                }
            }
        }
    }    
}

int main() {
    scanf("%d", &n);
    getchar();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                map[i][j][k] = getchar();
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                for (int t = 0; t < 6; ++t) {
                    int tx = i + dir[t][0],
                        ty = j + dir[t][1],
                        tz = k + dir[t][2];

                    if (!in(tx, ty, tz)) {
                        continue;
                    }

                    if (map[tx][ty][tz] == '?') {
                        uncert[0] = tx;
                        uncert[1] = ty;
                        uncert[2] = tz;
                        // printf("%d %d %d %d\n", __LINE__, tx, ty, tz);
                    } else if (map[tx][ty][tz] == '*') {
                        ++mines[i][j][k];
                    } 
                }    
            
            }
        }
    }

    // printf("\n%d %d %d\n", uncert[0], uncert[1], uncert[2]);

    for (int i = 0; i < 2; ++i) {
        // i = 0 -> ? is not mine
        // i = 1 -> ? is a mine
        for (int t = 0; t < 6; ++t) {
            mines[uncert[0] + dir[t][0]][uncert[1] + dir[t][1]][uncert[2] + dir[t][2]] += i;
        }
        // printf("%d %d\n", __LINE__, mines[2][1][2]);

        check(i);

        if (!invalid[i]) {
            puts("valid");
            if (i == 0) {
                int tot = 0;
                for (int t = 0; t < 6; ++t) {
                    if (map[uncert[0] + dir[t][0]][uncert[1] + dir[t][1]][uncert[2] + dir[t][2]] == '*') {
                        ++tot;
                    }
                }
                printf("%d", tot);
            } else {
                putchar('*');
            }
            return 0;
        }

        for (int t = 0; t < 6; ++t) {
            mines[uncert[0] + dir[t][0]][uncert[1] + dir[t][1]][uncert[2] + dir[t][2]] -= i;
        }        

    }

    puts("invalid");
    for (int i = 1; i <= cnt; ++i) {
        printf("%d %d %d\n", invalid_pos[i][0], invalid_pos[i][1], invalid_pos[i][2]);
    }

    return 0;
}