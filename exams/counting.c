#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define max(x, y) ((x) > (y) ? (x) : (y))
#define N 105

int r, c, ans;
char a[N][N];

int in(int x, int y) {
    return 0 <= x && x < r && 0 <= y && y < c;
}

void search(int x, int y) {
    for (int step = 1; step <= max(r, c); ++step) {
        int suc = 1;
        for (int k = 0; k < step; ++k) {
            if (!(in(x + k, y - k) && a[x + k][y - k] == '/')) {
                suc = 0;
                break;
            }
            if (!(in(x + k, y + k + 1) && a[x + k][y + k + 1] == '\\')) {
                suc = 0;
                break;
            }
            if (!(in(x + step + k, y - step + k + 1) && a[x + step + k][y - step + k + 1] == '\\')) {
                suc = 0;
                break;
            }
            if (!(in(x + step + k, y + step - k) && a[x + step + k][y + step - k] == '/')) {
                suc = 0;
                break;
            }
        }
        if (suc) {
            ans += suc;
        }
    }
}

int main() {
    freopen("counting.txt", "r", stdin);
    scanf("%d %d", &r, &c);
    char ch;
    getchar();
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            a[i][j] = getchar();
            // log("%c",a[i][j]);
        }
        getchar();
        // scanf("%s", a[i]);
    }

    log("");
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            putchar(a[i][j]);
        }
        puts("");
    }
    log("");
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (a[i][j] == '/' && a[i][j + 1] == '\\') {
                // log("i=%d,j=%d", i, j);
                // log("a[i][j]=%c, a[i][j+1]=%c", a[i][j], a[i][j + 1]);
                search(i, j);
            }
        }
    }
    printf("%d", ans);
    return 0;
}