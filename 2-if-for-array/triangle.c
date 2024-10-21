#include <stdio.h>

unsigned long long a, b, c;

int main() {
    scanf("%llu %llu %llu", &a, &b, &c);
    if (a + b <= c || a + c <= b || b + c <= a) {
        printf("not triangle");
    } else {
        if (a == b && b == c) {
            printf("equilateral triangle");
        } else if (a * a + b * b == c * c) {
            printf("right triangle");
        } else {
            if ((long long)(a * a + b * b - c * c) < 0) {
                printf("obtuse ");
            } else {
                printf("acute ");
            }
            if (a == b || b == c || c == a) {
                printf("isosceles ");
            }
            printf("triangle");
        }
    }
    return 0;
}