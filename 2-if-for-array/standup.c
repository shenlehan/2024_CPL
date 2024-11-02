#include <stdio.h>

int n, a[100005], ans;
long long tot;

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    tot = a[0];
    for (int i = 1; i <= n; ++i) {
        if (tot < i) {
            ans += i - tot;
            tot = i;
        }
        tot += a[i];
    }
    printf("%d", ans);
    return 0;
}