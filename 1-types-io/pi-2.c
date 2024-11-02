#include <stdio.h>
#include <math.h>

int main() {
    double pi = log(744.0 + 5280.0 * 5280.0 * 5280.0 * (236674.0 + 30303.0 * sqrt(61.0)) * (236674.0 + 30303.0 * sqrt(61.0)) * (236674.0 + 30303.0 * sqrt(61.0)));
    printf("%.15f\n", pi / sqrt(427));
    pi = 4.0 * (6.0 * atan(1.0 / 8.0) + 2.0 * atan(1.0 / 57.0) + atan(1.0 / 239.0));
    printf("%.15f", pi);
    return 0;
}