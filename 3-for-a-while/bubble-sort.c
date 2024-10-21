#include <stdio.h>

int T, n, a[50005];

int main() {
    scanf("%d", &T);
    
    while (T--) {

        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);

        int flag = 1;
        for (int i = 0; i < n - 1; ++i) {
            if (a[n - 1] < a[i]) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            puts("Yes");
        } else {
            puts("No");
        }

    }

    return 0;
}