#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int n, t;
long long k, ans;

int main() {
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= n; ++i) {
        k = k * 10 + t;
        ans += k;
    }
    printf("%lld", ans);
    return 0;
}