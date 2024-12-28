#include <stdio.h>

#define N 1005

int T, n, m, a[N], b[N], x[N], vis[N];

int main() {
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d", &n, &m); 
        int cnt = 0, t = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for (int i = 1; i <= m; ++i) scanf("%d", &x[i]);

        for (int i = 1; i <= m; ++i) {
            int temp = a[x[i]];
            for (int j = x[i]; j >= 2; --j) {
                a[j] = a[j - 1];
            }
            a[1] = temp;
        }


        int suc = 1;
        for (int i = 1; i < n; ++i) {
            if (a[i] > a[i + 1]) {
                suc = 0;
                puts("mayi is a good teacher");
                break;
            }
        }

        if (suc) {
            puts("I love C programming language");
        }

    }
    return 0;
}