#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef unsigned int ui;

ui l = 0, r = UINT_MAX;
char res[10];

int main() {
    while (1) {
        ui mid = l + (r - l) >> 1;
        printf("%u\n", mid);
        fflush(stdout);
        scanf("%s", res);
        if (res[0] == 'G') {
            r = mid - 1;
        } else if (res[0] == 'L') {
            l = mid + 1;
        } else if (res[0] == 'E') {
            break;
        }
    }
    return 0;
}