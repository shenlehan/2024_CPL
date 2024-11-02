#include <stdio.h>
#include <string.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

int t, x;
int a[15][15];
int win[10];

int main() {
    scanf("%d %d", &t, &x);

    while (t--) {
        int n;
        scanf("%d", &n);

        memset(a, 0, sizeof(a));
        memset(win, 0, sizeof(win));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &a[i][j]);
            }
        }

        for (int pig = 0; pig <= 2; ++pig) {
            int max_len = 0, tmp = 0;
            for (int i = 0; i < n; ++i) {
                tmp = 0;
                for (int j = 0; j < n; ++j) {
                    if (a[i][j] == (1 << pig)) {
                        ++tmp;
                    } else {
                        tmp = 0;
                    }
                    max_len = max(max_len, tmp);
                }
            }

            for (int i = 0; i < n; ++i) {
                tmp = 0;
                for (int j = 0; j < n; ++j) {
                    if (a[j][i] == (1 << pig)) {
                        ++tmp;
                    } else {
                        tmp = 0;
                    }
                    max_len = max(max_len, tmp);
                }
            }

            for (int i = 0; i < n; ++i) {
                tmp = 0;
                for (int j = 0; i + j < n; ++j) {
                    if (a[j][i + j] == (1 << pig)) {
                        ++tmp;
                    } else {
                        tmp = 0;
                    }
                    max_len = max(max_len, tmp);
                }
            } 

            for (int i = 0; i < n; ++i) {
                tmp = 0;
                for (int j = 0; j <= i; ++j) {
                    if (a[j][i - j] == (1 << pig)) {
                        ++tmp;
                    } else {
                        tmp = 0;
                    }
                    max_len = max(max_len, tmp);
                }
            }           
            if (max_len >= x) {
                win[pig] = 1;
            }
        }
        if (win[0] + win[1] + win[2] == 0 || win[0] + win[1] + win[2] >= 2) puts("draw");
        else {
            for (int i = 0; i <= 2; ++i) {
                if (win[i] == 1) {
                    printf("%d\n", 1 << i);
                    break;
                }
            }
        }
    }
    return 0;
}