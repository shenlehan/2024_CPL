#include <stdio.h>
#include <math.h>

int main() {
    long long p1, q1;
    scanf("%lld %lld", &p1, &q1);
    long double p = (long double)p1, q = (long double)q1;
    long double x1 = cbrt((-q / 2.0 + sqrt(q * q / 4.0 + p * p * p / 27.0)))
              + cbrt(-q / 2.0 - sqrt(q * q / 4.0 + p * p * p / 27.0));
    printf("%.3Lf", x1);
    return 0;
}