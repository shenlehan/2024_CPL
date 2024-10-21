#include <stdio.h>
const int mod = 1e9 + 7;

unsigned long long n, res, fac;

int main() {
    scanf("%llu", &n);
    fac = 1;
    for (unsigned long long i = 1; i <= n; ++i) {
        fac = fac * (i % mod) % mod;
        res = (res + (fac % mod)) % mod;
    }
    printf("%llu", res % mod);
    return 0;
}