#include <stdio.h>
#include <algorithm>
using namespace std;

int a[100] = {1, 1, 2, 3, 4, 4, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, 12, 17, 17, 19};


/**
 * hello world
 */
void func() {

}

int main() {
    int l = 0, r = 20;
    int mid;
    int x, pos = -1;
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
            r = mid - 1;
        }
    }
    int pos1 = lower_bound(a, a + 20, x) - a;
    printf("%d %d", pos, pos1);
    return 0;
}
