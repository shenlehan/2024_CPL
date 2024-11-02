#include <stdio.h>

int n, t, ans;

int calc(int pow) {
    int res = 0;
    while (pow >= 1) {
        res = res * 10 + t;
        --pow;
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= n; ++i) {
        ans += calc(i);
    }
    printf("%d", ans);
    return 0;
}