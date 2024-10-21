#include <stdio.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

int n, m = -1, tot;

int main() {
    scanf("%d", &n);
    while (n != 1) {
        ++tot;
        m = max(m, n);
        if (n % 2 == 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
    }
    printf("%d %d", tot, m);
    return 0;
}