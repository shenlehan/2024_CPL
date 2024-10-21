#include <stdio.h>
#include <math.h>

int n, k;
double x[105], t[25], ep[105], sum;

int main() {
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; ++i) {
        scanf("%lf", &x[i]);
    }
    for (int i = 1; i <= k; ++i)
        scanf("%lf", &t[i]);

    for (int i = 1; i <= k; ++i) {
        sum = 0;
        for (int j = 1; j <= n; ++j) {
            ep[j] = exp(x[j] / t[i]);
            sum += ep[j];
        }

        double E = 0;
        for (int j = 1; j <= n; ++j) {
            printf("%.3lf ", ep[j] / sum);
            E += ep[j] / sum;
        }
        E /= n;

        double var = 0;
        for (int j = 1; j <= n; ++j) {
            var += (ep[j] / sum - E) * (ep[j] / sum - E);
        }
        var /= n;

        printf("%.3lf\n", var);

    }

    return 0;
}