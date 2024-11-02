#include <stdio.h>

int n, m, a[505][505];
int posx[505], pos[505];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
    
    for (int num = 1; num <= n * m / 2; ++num) {
        // find num pos
        int x1, y1, x2, y2, first = 1, found = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (a[i][j] == num) {
                    if (first) {
                        first = 0;
                        x1 = i, y1 = j;
                    } else {
                        x2 = i, y2 = j;
                        found = 1;
                        break;
                    }
                }
            }
            if (found) {
                break;
            }
        }

   //     printf("(%d %d) (%d %d)\n", x1, y1, x2, y2);

        // left
        int tx = x1, ty = y1;


    }

    return 0;
}