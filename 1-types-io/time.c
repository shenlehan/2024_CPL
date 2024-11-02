#include <stdio.h>

typedef char string[20];

int main() {
    string month, weekday;
    int day, hour, minute, second, year;
    scanf("%s %d %d %s %d %d %d", month, &day, &year, weekday, &hour, &minute, &second);
    printf("%.3s %.3s %.2d %.2d:%.2d:%.2d %.4d", weekday, month, day, hour, minute, second, year);
    return 0;
}