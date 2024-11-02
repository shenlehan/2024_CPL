#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define num(x) (x - '0')

int m, n;
int s[2005], tmp[2005], prev[2005];

int judge(int a, int b, int c) {
    if (a == 1) {
        if (b == 1 && c == 1) {
            return 0;
        } else if (b + c == 1) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (b + c >= 1) {
            return 1;
        } else {
            return 0;
        }
    }
}

int main() {
    scanf("%d %d ", &n, &m);

    for (int i = 1; i <= n; ++i) {
        scanf("%1d", &s[i]);
    }

    memcpy(prev, s, sizeof(prev));
    
    while (--m) {
        for (int i = 1; i <= n; ++i) {
            tmp[i] = judge(prev[i - 1], prev[i], prev[i + 1]);
        }
        
        memcpy(prev, tmp, sizeof(tmp));

        for (int i = 1; i <= n; ++i) {
            printf("%d", tmp[i]);
        }

        puts("");
    }

    return 0;
}