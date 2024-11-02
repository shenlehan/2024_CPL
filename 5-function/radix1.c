#include <stdio.h>
#include <math.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

int p[5], q[5], r[5], b, maxv, p1, q1, r1;

int main() {
    scanf("%d %d %d", &p1, &q1, &r1);
    p[0] = p1 % 10, p[1] = p1 / 10;
    q[0] = q1 % 10, q[1] = q1 / 10;
    r[0] = r1 % 10, r[1] = r1 / 10;

    for (int i = 0; i <= 1; ++i)
        maxv = max(maxv, p[i]);
    for (int i = 0; i <= 1; ++i)
        maxv = max(maxv, q[i]);
    for (int i = 0; i <= 1; ++i)
        maxv = max(maxv, r[i]);

    for (b = maxv + 1; b <= 40; ++b) {
        int A = p[1] * q[1] * b * b;
        int B = b * (p[0] * q[1] + p[1] * q[0] - r[1]);
        int C = p[0] * q[0] - r[0];
        if (A + B + C == 0) {
            printf("%d", b);
            return 0;
        }
    }
    printf("0");
    
    return 0;
}