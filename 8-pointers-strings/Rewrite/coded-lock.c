#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 1005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define min(x, y) ((x) < (y) ? (x) : (y))
#define ll long long

int w, n, d;
ll ans;
int arr[N], vis[100005];

int main() {
    scanf("%d %d %d", &w, &n, &d);
    for (int i = 1; i <= w; ++i)
        scanf("%d", &arr[i]);

    for (int i = 1; i <= (w >> 1); ++i) {
        if (arr[i] == arr[w - i + 1]) {
            continue;
        }

        // back
        int k = arr[i], cnt1 = 0, cnt2 = 0, tmp = 0x7fffffff;
        int f1 = 0, f2 = 0;
        do {
            k += d;
            ++cnt1;
            if (k > n) {
                k %= n; 
            }
            if (k == arr[w - i + 1]) {
                tmp = min(tmp, cnt1);
                f1 = 1;
                break;
            }
        } while (k != arr[i]);

        k = arr[i];
        do {
            k -= d;
            ++cnt2;
            if (k <= 0) {
                k = (k % n + n) % n; 
            }
            if (k == arr[w - i + 1]) {
                tmp = min(tmp, cnt2);
                f2 = 1;
                break;
            }
        } while (k != arr[i]);
        
        if (!f1 && !f2) {
            printf("Impossible");
            return 0;
        } else if (f1) {
            ans += cnt1;
        } else if (f2) {
            ans += cnt2;
        } else {
            ans += min(cnt1, cnt2);
        }
    }

    printf("%lld", ans);

    return 0;
}