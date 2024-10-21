#include <stdio.h>

int m;
double x[105], y[105];

int main() {
    scanf("%d", &m);

    for (int i = 1; i <= m; ++i)
        scanf("%lf %lf", &x[i], &y[i]);

    double c0 = 1.0, c1 = 1.0, a = 0.01;
    int T = 2000;

    while (T--) {
        double tmp1 = 0, tmp2 = 0;
        for (int i = 1; i <= m; ++i) {
            tmp1 += (c0 + c1 * x[i]) - y[i];
            tmp2 += ((c0 + c1 * x[i]) - y[i]) * x[i];
        }

        c0 -= a * tmp1 / m;
        c1 -= a * tmp2 / m;
    }

    printf("y = %.3lf + %.3lfx", c0, c1);

    return 0;
}