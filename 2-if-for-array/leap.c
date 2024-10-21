#include <stdio.h>

int main() {
    unsigned long long year, k;
    scanf("%llu %llu", &year, &k);

    if (year % 4 != 0) {
        puts("Normal year!");
    } else if (year % 100 != 0) {
        puts("Leap year!");
    } else if (year % 400 != 0) {
        puts("Normal year!");
    } else {
        puts("Leap year!");
    }

    year += k;
    if (year % 4 != 0) {
        puts("Normal year!");
    } else if (year % 100 != 0) {
        puts("Leap year!");
    } else if (year % 400 != 0) {
        puts("Normal year!");
    } else {
        puts("Leap year!");
    }    

    return 0;
}