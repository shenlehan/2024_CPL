#include <stdio.h>
#include <math.h>

const double R = 8.314;

int main() {
    double p, l, t;
    scanf("%lf %lf %lf", &p, &l, &t);
    printf("%.4e", p * pow(l, 3.0) / (R * t));
    return 0;
}