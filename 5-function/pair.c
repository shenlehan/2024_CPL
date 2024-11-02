#include <stdio.h>
#include <stdlib.h>
#define N 1000005
#define min(x, y) ((x) < (y) ? (x) : (y))

int n, m, t, ans = 0x7fffffff;
int a[N], b[N];

int binary(int k) {
    int left = 0;
    int right = n;
    int pos = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] <= k) {
            left = mid + 1; // 查找右半部分
            pos = mid;
        } else {
            right = mid - 1;
        }
    }

    return pos;
}

int main() {
    scanf("%d %d %d", &n, &m, &t);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i)
        scanf("%d", &b[i]);
    for (int i = 0; i < m; ++i) {
        int pos = binary(t - b[i]);
        if (pos == -1) {
            continue;
        }
        ans = min(ans, t - b[i] - a[pos]);
    }
    printf("%d", ans == 0x7fffffff ? -1 : ans);
    return 0;
}