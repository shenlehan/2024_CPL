#include <stdio.h>
#include <string.h>

double a[5][5], d[5];
double delta[5];
double tmp[5][5];

double calc(double b[5][5]) {
    double res = 0;
    res = b[1][1] * b[2][2] * b[3][3] + b[1][2] * b[2][3] * b[3][1] + b[1][3] * b[2][1] * b[3][2] -
          b[1][1] * b[2][3] * b[3][2] - b[1][2] * b[2][1] * b[3][3] - b[1][3] * b[2][2] * b[3][1];

    return res;
}

int main() {
    for (int i = 1; i <= 3; ++i) {
        scanf("%lf %lf %lf %lf", &a[i][1], &a[i][2], &a[i][3], &a[i][4]);
    }

    memcpy(tmp, a, sizeof(a));
    delta[0] = calc(tmp);

    for (int i = 1; i <= 3; ++i) {
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, a, sizeof(a));
        for (int j = 1; j <= 3; ++j) {
            tmp[j][i] = a[j][4];
        }
        delta[i] = calc(tmp);
    }

    printf("%.2f %.2f %.2f", delta[1] / delta[0], delta[2] / delta[0], delta[3] / delta[0]);

    return 0;
}