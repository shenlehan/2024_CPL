#include <stdio.h>
#include <stdlib.h>

#define N 105

typedef long long LL;

typedef struct Node {
    LL t, d;
} Node;

Node a[N];
LL latest[N];
int n;

int cmp(const void *t1, const void *t2) {
    return ((((Node *)t1)->d) > (((Node *)t2)->d)) - ((((Node *)t1)->d) < (((Node *)t2)->d));
}

int main() {
    freopen("ddl.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &a[i].t, &a[i].d);
    }
    qsort(a, n, sizeof(Node), cmp);
    latest[n - 1] = a[n - 1].d - a[n - 1].t;
    for (int i = n - 2; i >= 0; --i) {
        // printf("%lld %lld\n", a[i].t, a[i].d);
        latest[i] = a[i].d - a[i].t;

        if (a[i].d > latest[i + 1]) {
            latest[i] = latest[i + 1] - a[i].t;
        }
        if (latest[i] < latest[i + 1] && latest[i + 1] < latest[i] + a[i].t) {
            puts("-1");
            return 0;
        }
    }
    if (latest[0] < 0) printf("-1");
    else printf("%lld", latest[0]);
    return 0;
}