#include <stdio.h>

int T, n, a[50005];

int main() {
    scanf("%d", &T);
    
    while (T--) {

        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 2; j++) { // not j < n - i - 1
                if (a[j] > a[j + 1]) {
                    int tmp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp;
                }
            }
        }

        int flag = 1;

        for (int i = 0; i < n - 1; ++i) {
            if (a[i] > a[i + 1]) {
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