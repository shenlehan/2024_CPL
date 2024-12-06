#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 1000005
#define min(x, y) ((x) < (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int n, m, t, a[N], b[N], ans = 0x7fffffff;

int binary_search(int k) {
    int l = 0, r = n - 1, pos = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (k - a[mid] >= 0) {
            pos = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if (pos == -1) {
        return -1;
    } else {
        return pos;
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &t);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d", &b[i]);
    }

    for (int i = 0; i < m; ++i) {
        int k = t - b[i];
        // k >= a[i] && k - a[i] min
        int t = binary_search(k);
        if (t == -1) continue;
        ans = min(ans, k - a[t]);
    }
    printf("%d", ans == 0x7fffffff ? -1 : ans);

    return 0;
}