#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) :(y))
#define N 1005

int w, n, d, ans;
int pw[N];

int main() {
    scanf("%d %d %d", &w, &n, &d);
    for (int i = 1; i <= w; ++i)
        scanf("%d", &pw[i]);

    for (int i = 1; i <= (w >> 1); ++i) {
        if (pw[i] == pw[w - i + 1]) {
            continue;
        }

        int ans1 = 0, ans2 = 0;
        int fail1 = 0, fail2 = 0;
        int k = pw[i];
        while (k != pw[w - i + 1]) {
            k += d;
            while (k > n) {
                k -= n;
            }
            ++ans1;
            if (k == pw[i]) {
                ans1 = 0x7fffffff;
                fail1 = 1;
                break;
            }
        }

        k = pw[i];
        while (k != pw[w - i + 1]) {
            k -= d;
            while (k <= 0) {
                k += n;
            }
            ++ans2;
            if (k == pw[i]) {
                fail2 = 1;
                ans2 = 0x7fffffff;
                break;
            }
        }
        if (fail1 && fail2) {
            puts("Impossible");
            return 0;
        } else {
            ans += min(ans1, ans2);
        }
    }
    printf("%d", ans);
    
    return 0;
}