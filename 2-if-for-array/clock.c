#include <stdio.h>

int main() {
    int hour, minute;
    char ch;
    scanf("%d%c%d", &hour, &ch, &minute);
    if (hour < 12) {
        printf("%.2d:%.2d a.m.", hour, minute);
    } else if (hour == 12) {
        printf("12:%.2d p.m.", minute);
    } else {
        printf("%.2d:%.2d p.m.", hour % 12, minute);
    }
    return 0;
}