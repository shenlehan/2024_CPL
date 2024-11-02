#include <stdio.h>

int n, n1, n2, cnt, ans;

int qpow(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            res *= a;
        }
        a *= a;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    n1 = n2 = n;
    while (n1) {
        ++cnt;
        n1 /= 10;
    }
    for (int i = 0; i < cnt; ++i) {
        n1 += qpow(n2 % 10, cnt);
        n2 /= 10;
    }
    if (n1 == n) {
        printf("%d", cnt);
    } else {
        printf("0");
    }
    return 0;
}