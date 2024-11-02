#include <stdio.h>
#include <math.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

int p[5], q[5], r[5], b, maxv, p1, q1, r1;

int main() {
    scanf("%d %d %d", &p1, &q1, &r1);
    p[0] = p1 % 10, p[1] = p1 / 10;
    q[0] = q1 % 10, q[1] = q1 / 10;
    r[0] = r1 % 10, r[1] = r1 / 10;

    int A = p[1] * q[1];
    int B = p[0] * q[1] + p[1] * q[0] - r[1];
    int C = p[0] * q[0] - r[0];

    int delta = B * B - 4 * A * C;

    if (delta < 0) {
        printf("0");
        return 0;
    }

    if (delta != 0 && delta % (int)(sqrt(delta)) != 0) {
        puts("0");
        return 0;
    }

    if (A != 0) {
        if ((-1 * B + (int)sqrt(delta)) % (2 * A) != 0) {
            puts("0");
            return 0;
        }
        b = ((-1.0 * B + sqrt(delta)) / (2.0 * A));
    } else if (B != 0) {
        if (C % B != 0) {
            printf("0");
            return 0;
        }
        b = -1 * C / B;
    } else {
        b = 0;
    }
    printf("%d", b);
    return 0;
}