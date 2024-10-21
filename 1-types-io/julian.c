#include <stdio.h>

int year, month, day;

int main() {
    scanf("%d %d %d", &year, &month, &day);
    int a = (int)(14.0 - month) / 12.0,
        y = year + 4800 - a,
        m = month + 12 * a - 3,
        jdn = day + (int)((153.0 * m + 2) / 5.0) + 365 * y + (int)(y / 4) - (y / 100) + (y / 400) -32045;
    printf("%d", jdn);
    return 0;
}