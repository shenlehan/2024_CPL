#include <stdio.h>
const int mod = 10007;

int n, fac = 1, ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        ans = ((fac * (i % mod) % mod) + ans % mod) % mod;
        fac = ((fac % mod) * i) % mod;
    }
    printf("%d", ans);
    return 0;
}