#include <stdio.h>

int live[505], nxt[505], n, k, tot;

int main() {
    scanf("%d %d", &n, &k);
    tot = n;

    for (int i = 1; i < n; ++i) {
        nxt[i] = (i + 1);
    }
    nxt[n] = 1;

    int start = 1;
    while (tot > 1) {
        int i, cnt = 0;
        for (i = start; ; ) {
            ++cnt;
            if (cnt == k - 1) {
                break;
            }
            i = nxt[i];
        }

        live[nxt[i]] = 1;
        start = nxt[nxt[i]];
        nxt[i] = nxt[nxt[i]]; // 链表不要太早跳到下一个
        --tot;

    }

    for (int i = 1; i <= n; ++i)
        if (!live[i])
            printf("%d\n", i);

    return 0;
}