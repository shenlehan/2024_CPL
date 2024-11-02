#include <stdio.h>
#include <stdlib.h>
typedef long long ll;

int len, n;
char *str;
ll res, fac = 1;

int num(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    else if (ch == 'A') return 10;
    else if (ch == 'B') return 11;
    else if (ch == 'C') return 12;
    else if (ch == 'D') return 13;
    else if (ch == 'E') return 14;
    else if (ch == 'F') return 15;
    else return -1;
}

int check(char ch) { // ok -> 1, not ok -> 0
    if (num(ch) == -1)
        return 0;
    if (num(ch) < 0 || num(ch) > n - 1)
        return 0;
    else 
        return 1;
}

int main() {
    scanf("%d %d", &len, &n);
    str = malloc(len + 1);
    scanf("%s", str);

    for (int i = 0; i < len; ++i) {
        if (!check(str[i])) {
            puts("Error");
            return 0;
        }
    }

    res = num(str[len - 1]);
    for (int i = len - 2; i >= 0; --i) {
        fac *= n;
        res += fac * num(str[i]);
    }

    printf("%lld", res);

    return 0;
}