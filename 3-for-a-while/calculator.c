#include <stdio.h>
typedef long long ll;

ll a, b;
char op[5];

ll quick_pow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            res *= a;
        a *= a;
    }
    return res;
}

int main() {
    while (scanf("%lld %s %lld", &a, op, &b) != EOF) {
        if (op[0] == '+')
            printf("%lld\n", a + b);
        else if (op[0] == '-')
            printf("%lld\n", a - b);
        else if (op[0] == '*') {
            if (op[1] == '\0')
                printf("%lld\n", a * b);
            else if (op[1] == '*')
                printf("%lld\n", quick_pow(a, b));
        } else if (op[0] == '/') {
            if (op[1] == '\0') {
                printf("%lld\n", a / b);
            } else if (op[1] == '*') {
                printf("%.3f\n", 1.0 * a / b);
            }
        } else if (op[0] == '%') {
            printf("%lld\n", a % b);
        }
    }
    return 0;
}