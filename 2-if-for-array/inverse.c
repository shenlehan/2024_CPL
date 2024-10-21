#include <stdio.h>

int n, k, len;
char str[100000001], ch;

int main() {
    scanf("%d ", &n);
    for (int i = 0; i < n; ++i) {
        str[i] = getchar();
    }
    scanf(" %d", &k);
    if (k == 0 || k == n) {
        for (int i = n - 1; i >= 0; --i) {
            printf("%c", str[i]);
        }
        return 0;     
    }
    for (int i = k - 1; i >= 0; --i) {
        printf("%c", str[i]);
    }
    for (int i = n - 1; i >= k; --i) {
        printf("%c", str[i]);
    }    
    return 0;
}