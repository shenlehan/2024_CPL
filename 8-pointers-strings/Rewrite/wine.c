#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

struct wine {
    int val, num;
} w[10005];

int n, l;
long long ans;

int cmp(const void *a, const void *b) {
    struct wine *w1 = (struct wine *) a;
    struct wine *w2 = (struct wine *) b;
    return (w1->val > w2->val) - (w1->val < w2->val);
}

int main() {
    scanf("%d %d", &n, &l);
    for (int i = 0; i < n; ++i)
        scanf("%d", &w[i].val);
    for (int i = 0; i < n; ++i)
        scanf("%d", &w[i].num);
    
    qsort(w, n, sizeof(struct wine), cmp);

    for (int i = n - 1; i >= 0; --i) {
        if (l >= w[i].num) {
            l -= w[i].num;
            ans += w[i].num * w[i].val;
        } else {
            ans += l * w[i].val;
            break;
        }
    }

    printf("%lld", ans);

    return 0;
}