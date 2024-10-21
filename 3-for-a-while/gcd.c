#include <stdio.h>
typedef long long ll;

ll a, b;

ll gcd(ll a, ll b) {
    if (a % b == 0) {
        return b;
    }
    return gcd(b, a % b);
}

int main() {
    scanf("%lld %lld", &a, &b);
    printf("%lld", gcd(a, b));
    return 0;
}