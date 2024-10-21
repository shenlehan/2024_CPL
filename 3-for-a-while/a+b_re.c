#pragma GCC optimize(2)
#include <stdio.h>
#include <string.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

char a[1005], b[1005];
int c[1005], a1[1005], b1[1005];

int main() {
    while (scanf("%s %s", a, b) != EOF) {
        int lena = strlen(a);
        int lenb = strlen(b);

        for (int i = 0; i < 1005; ++i)
            a1[i] = b1[i] = 0;

        for (int i = 0; i < lena; ++i)
            a1[i] = a[lena - i - 1] - '0';

        for (int i = 0; i < lenb; ++i)
            b1[i] = b[lenb - i - 1] - '0';      

        int lenc = 0;
        for (int i = 0, up = 0; i <= max(lena, lenb) + 1; ++i) {
            c[i] = a1[i] + b1[i] + up;
            up = 0;
            if (c[i] >= 10) {
                up = c[i] / 10;
                c[i] = c[i] % 10;
            }
            ++lenc;
        }

        while (c[lenc] == 0)
            --lenc;
        for (int i = lenc; i >= 0; --i) {
            printf("%d", c[i]);
        }
        puts("");
    }
    return 0;
}