#include <stdio.h>
#define N 1510

int n, k, l, b;
int nxt[N], shot[N];

int main() {
    scanf("%d %d %d %d", &n, &k, &b, &l);
    
    for (int i = 1; i <= n - 1; ++i)
        nxt[i] = i + 1;
    nxt[n] = 1;

    int cur = b, res = n, start = 1;
    while (res > 1) {
        int cnt = 0, i; // notice cnt
        for (i = start; ; ) {
            ++cnt;
            if (cnt == k - 1) {
                break;
            }
            i = nxt[i];
        }

        // shot nxt[i]
        if (cur >= 1) {
            shot[nxt[i]]++;
            --cur;
        } else {
            cur = b;
        }

        start = nxt[nxt[i]];
        if (shot[nxt[i]] == l) {
            --res;
            nxt[i] = nxt[nxt[i]];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (shot[i] < l) {
            printf("%d\n", i);
            return 0;
        }
    }

    return 0;
}