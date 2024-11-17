#pragma GCC optimize(2)
#include <stdio.h>
#define N 100005
#define min(x, y) ((x) < (y) ? (x) : (y))
#define abs(x) ((x) >= 0 ? (x) : -(x))

int w, n, d, ans;
int pw[N], seq[N], vis[N], cnt[N], tot, num[N];

int main() {
    scanf("%d %d %d", &w, &n, &d);
    for (int i = 1; i <= w; ++i)
        scanf("%d", &pw[i]);

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            ++tot;
            int k = i;
            do {
                // printf("Now: %d in group %d\n", k, tot);
                vis[k] = 1;
                seq[k] = ++cnt[tot];
                num[k] = tot;
                k = ((k + d) % n == 0) ? n : ((k + d) % n);
            } while (k != i);
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     printf("%d ", seq[i]);
    // }
    // puts("");

    for (int i = 1; i <= (w >> 1); ++i) {
        if (pw[i] == pw[w - i + 1]) {
            continue;
        }

        if (num[pw[i]] != num[pw[w - i + 1]]) {
            puts("Impossible");
            return 0;
        }

        int k = abs(seq[pw[i]] - seq[pw[w - i + 1]]);
        // printf("now :%d\n", k);
        // printf("%d %d %d\n", __LINE__, seq[pw[i]], seq[pw[w - i + 1]]);
        ans += min(k, cnt[num[pw[i]]] - k);
    }

    printf("%d", ans);

    return 0;
}