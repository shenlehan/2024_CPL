#include <stdio.h>

char str[2005];
int mid, n;

int main() {
    scanf("%d %s", &n, str);

    for (int i = 0; i < (n >> 1); ++i) {
        if (str[i] == '?') {
            str[i] = str[n - i - 1];
        } else if (str[n - i - 1] == '?') {
            str[n - i - 1] = str[i];
        }
    }

    printf("%s", str);

    return 0;
}