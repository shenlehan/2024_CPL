#include <stdio.h>

double x, res, tmp;
int n;

double qpow(double t, int m) {
    double res = 1.0;
    while (m--) {
        res *= t;
    }
    return res;
}

int main() {
    scanf("%lf %d", &x, &n);
    for (int i = 0; i <= n; ++i) {
        tmp = qpow(x, 2 * i + 1) / (2.0 * i + 1.0);
        if (i % 2 == 0) {
            res += tmp;
        } else {
            res -= tmp;
        }
    }
    printf("%.10f", 4.0 * res);
    return 0;
}