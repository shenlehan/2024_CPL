#include <stdio.h>

int a[100] = {1, 1, 2, 3, 4, 4, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, 12, 17, 17, 19};

int main() {
    int l = 0, r = 15;
    int mid;
    int x, pos;
    scanf("%d", &x);
    while (l <= r) {
        mid = (l + r) >> 1;
        printf("Current l:%d, r:%d, mid:%d\n", l, r, mid);
        if (a[mid] < x) {
            l = mid + 1;
        } else if (a[mid] > x) {
            r = mid - 1;
        } else {
            pos = mid;
            l = mid + 1;
        }
    }
    printf("%d", pos);
    return 0;
}