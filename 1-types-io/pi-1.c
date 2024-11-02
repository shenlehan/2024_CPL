#include <stdio.h>
#include <math.h>

int main() {
    double pi = 16.0 * atan(1.0 / 5.0) - 4.0 * atan(1.0 / 239.0);
    printf("%.15f\n", pi);
    pi = log(pow(640320.0, 3.0) + 744.0) / sqrt(163.0);
    printf("%.15f", pi);
    return 0;
}