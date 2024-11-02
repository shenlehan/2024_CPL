#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int n, dig[10];

bool prime(int x) {
    int tmp = sqrt(x + 0.5);
    if (x == 2 || x == 3 || x == 5)
        return true;
    for (int i = 2; i <= tmp; ++i)
        if (x % i == 0)
            return false;
    
    return true;
}

int calc(int x) {
    if (x <= 9)
        return x;
    int len = 0, res = 0;
    while (x) {
        dig[++len] = x % 10;
        x /= 10;
    }

    for (int i = 1; i <= len; ++i) {
        res = res * 10 + dig[i];
    }
    return res;
}

int main() {
    scanf("%d", &n);
    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        int rev = calc(i);
        if (prime(i) && prime(rev))
            ++ans;
    }
    printf("%d", ans);
    return 0;
}