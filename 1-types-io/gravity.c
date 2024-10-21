#include <stdio.h>

int main() {
    double m, r;
    scanf("%lf %lf", &m, &r);
    double f = 6.674e-11 * 77.15 * m / (r * r);
    printf("%.3e", f);
    return 0;
}