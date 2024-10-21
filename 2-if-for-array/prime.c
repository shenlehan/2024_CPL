#pragma GCC optimize(2)
#include <stdio.h>
#include <math.h>
#include <string.h>

int n, cnt, prime[5000010], isprime[50000000 + 10];

int main() {
    scanf("%d", &n);
    isprime[1] = 0;
    memset(isprime, 0x3f, sizeof(isprime));
    for (register int i = 2; i <= n; ++i) {
        if (isprime[i]) {
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
            isprime[i * prime[j]] = 0;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
    printf("%d", cnt);
    return 0;
}