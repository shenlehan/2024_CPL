#include <stdio.h>
#define CORRECT ((1 << 10) - 2)

int a[10][10];

int main() {
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
    
    // col
    for (int i = 1; i <= 9; ++i) {
        int check = 0;
        for (int j = 1; j <= 9; ++j) {
            check |= (1 << a[i][j]);
        }
        if (check != CORRECT) {
            puts("NO");
            return 0;
        }
    }

    // rol
    for (int i = 1; i <= 9; ++i) {
        int check = 0;
        for (int j = 1; j <= 9; ++j) {
            check |= (1 << a[j][i]);
        }
        if (check != CORRECT) {
            puts("NO");
            return 0;
        }
    }

    // box
    for (int i = 1; i <= 9; i += 3) {       
        for (int j = 1; j <= 9; j += 3) {
            int check = 0;
            check |= (1 << a[i][j]);
            check |= (1 << a[i][j + 1]);
            check |= (1 << a[i][j + 2]);
            check |= (1 << a[i + 1][j]);
            check |= (1 << a[i + 1][j + 1]);
            check |= (1 << a[i + 1][j + 2]);
            check |= (1 << a[i + 2][j]);
            check |= (1 << a[i + 2][j + 1]);
            check |= (1 << a[i + 2][j + 2]);

            if (check != CORRECT) {
                puts("NO");
                return 0;
            }
        }
    }

    puts("YES");

    return 0;
}