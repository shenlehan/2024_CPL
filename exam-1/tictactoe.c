#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define log(f, args...) do { printf("%d, %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define max(x, y) ((x) > (y) ? (x) : (y))

int t, x;
int map[15][15];
int win[5]; // win[i] digit 0 / 1 / 2 pig i 

int main() {
    scanf("%d %d", &t, &x);

    while (t--) {
        int n;
        scanf("%d", &n);

        memset(map, 0, sizeof(map));
        memset(win, 0, sizeof(win));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &map[i][j]);
            }
        }

        // col
        for (int pig = 1; pig <= 4; ++pig) {
            if (pig == 3) {
                continue;
            }
            for (int i = 0; i < n; ++i) {
                int tmp = 0, max_len = -1;
                for (int j = 0; j < n; ++j) {
                    if (map[j][i] == pig) {
                        ++tmp;
                        max_len = max(max_len, tmp);
                    } else {
                        max_len = max(max_len, tmp);
                        tmp = 0;
                    }
                }
                max_len = max(max_len, tmp);
                if (max_len >= x)
                    win[pig] = 1;
            }
        }

        // row
        for (int pig = 1; pig <= 4; ++pig) {
            if (pig == 3) {
                continue;
            }
            for (int i = 0; i < n; ++i) {
                int tmp = 0, max_len = -1;
                for (int j = 0; j < n; ++j) {
                    if (map[i][j] == pig) {
                        ++tmp;
                        max_len = max(max_len, tmp);
                    } else {
                        max_len = max(max_len, tmp);
                        tmp = 0;
                    }
                }
                max_len = max(max_len, tmp);
                if (max_len >= x)
                    win[pig] = 1;
            }
        }

        // X
        for (int pig = 1; pig <= 4; ++pig) {
            if (pig == 3) {
                continue;
            }
            for (int i = 0; i < n; ++i) {
                int tmp = 0, max_len = -1;
                for (int j = 0; i + j < n; ++j) {
                    if (map[i + j][j] == pig) {
                        ++tmp;
                        max_len = max(max_len, tmp);
                    } else {
                        max_len = max(max_len, tmp);
                        tmp = 0;
                    }
                }
                max_len = max(max_len, tmp);
                if (max_len >= x)
                    win[pig] = 1;
            }
        }
        for (int pig = 1; pig <= 4; ++pig) {
            if (pig == 3) {
                continue;
            }
            for (int i = 0; i < n; ++i) {
                int tmp = 0, max_len = -1;
                for (int j = 0; i - j >= 0; ++j) {
                    if (map[i - j][j] == pig) {
                        ++tmp;
                        max_len = max(max_len, tmp);
                    } else {
                        max_len = max(max_len, tmp);
                        tmp = 0;
                    }
                }
                max_len = max(max_len, tmp);
                if (max_len >= x)
                    win[pig] = 1;
            }
        }
        if (win[1] + win[2] + win[4] == 0 || win[1] + win[2] + win[4] >= 2) {
            puts("draw");
        } else {
            for (int i = 1; i <= 4; ++i) {
                if (i == 3) {
                    continue;
                }
                if (win[i] == 1) {
                    printf("%d\n", i);
                    break;
                }
            }
        }
    }
    return 0;
}