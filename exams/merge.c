#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long long a[200005], b[200005], c[400005];
long long n1, n2, p1, p2, t1 = 1, t2 = 1, tot;

int main() {
    a[0] = b[0] = LLONG_MIN;
    scanf("%lld", &n1);
    for (long long i = 1; i <= n1; ++i) {
        scanf("%lld", &a[i]);
        if (a[i] > a[t1]) t1 = i;
    }

    scanf("%lld", &n2);
    for (long long i = 1; i <= n2; ++i) {
        scanf("%lld", &b[i]);
        if (b[i] > b[t2]) t2 = i;
    }
    
    // printf("%d %d\n", t1, t2);
    p1 = 1, p2 = 1;
    while (p1 <= t1 && p2 <= t2) {
        if (a[p1] < b[p2]) {
            c[++tot] = a[p1++];
        } else {
            c[++tot] = b[p2++];
        }
    }
    while (p1 <= t1) c[++tot] = a[p1++];
    while (p2 <= t2) c[++tot] = b[p2++];
    while (p1 <= n1 && p2 <= n2) {
        if (a[p1] > b[p2]) {
            c[++tot] = a[p1++];
        } else {
            c[++tot] = b[p2++];
        }
    }
    while (p1 <= n1) c[++tot] = a[p1++];
    while (p2 <= n2) c[++tot] = b[p2++];
    for (long long i = 1; i <= tot; ++i) printf("%lld ", c[i]);
    return 0;
}