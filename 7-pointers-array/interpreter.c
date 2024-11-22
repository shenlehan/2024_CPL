#include <stdio.h>

int x;

int main() {
    scanf("%x", &x);
    printf("%d\n", x);
    printf("%u\n", *(&x));
    float *f = &x;
    printf("%.6f\n", *f);
    printf("%.3e\n", *f);   
    return 0;
}