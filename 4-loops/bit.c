#include <stdio.h>

int a, b;
int bit[35][2];

int calc(int x, int p) {
    int t = 0;
    while (x) {
        bit[t++][p] = x & 1;
        x >>= 1;
    }
    return t;
}

int main() {
    scanf("%d %d", &a, &b);
    int lena = calc(a, 0), lenb = calc(b, 1);
    
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        res += (bit[i][0] & bit[i][1]) << (i);
    }
    printf("%d\n", res);

    res = 0;
    for (int i = 0; i < 32; ++i) {
        res += (bit[i][0] | bit[i][1]) << (i);
    }
    printf("%d\n", res);

    res = 0;
    for (int i = 0; i < 32; ++i) {
        res += (bit[i][0] ^ bit[i][1]) << (i);
    }
    printf("%d\n", res);

    res = 0;
    for (int i = 0; i < 32; ++i) {
        res += (!bit[i][0]) << (i);
    }
    printf("%d\n", res);

    res = 0;
    for (int i = 0; i < 32; ++i) {
        res += (bit[i][0] << i) * (1 << b);
    }
    printf("%d\n", res);

    printf("%d\n", a / (1 << b));

    printf("%d\n", bit[b][0]);

    res = 0;
    for (int i = 0; i < 32; ++i) {
        res += bit[i][0];
    }
    printf("%d\n", res);

    return 0;
}