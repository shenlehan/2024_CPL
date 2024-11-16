#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 10005

int n, l;
long long ans;

struct wine {
    int v, w;
} a[N];

int main() {
    scanf("%d %d", &n, &l);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i].v);

    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i].w);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i].v < a[j].v) {
                struct wine tmp;
                memcpy(&tmp, &a[i], sizeof(struct wine));
                memcpy(&a[i], &a[j], sizeof(struct wine));
                memcpy(&a[j], &tmp, sizeof(struct wine));
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (l >= a[i].w) {
            ans += a[i].w * a[i].v;
            l -= a[i].w;
        } else {
            ans += a[i].v * l;
            break;
        }
    }

    printf("%lld", ans);

    return 0;
}