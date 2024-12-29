#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef long long LL;

int n;
char comd[5], str[30];

void Ternary(LL x) {
    LL sign;
    if (x == 0) {
        puts("0 0");
        return;
    } else if (x < 0) {
        sign = -1;
    } else {
        sign = 1;
    }

    printf("%lld ", x);

    x = x * sign;
    int buf[25], len = 0;
    memset(buf, 0, sizeof(buf));
    while (x > 0) {
        buf[len++] = x % 3;
        x /= 3;
    }
    for (int i = 0; i < len; ++i) {
        if (buf[i] == 0 | buf[i] == 1) continue;
        else if (buf[i] == 2) buf[i] = -1, ++buf[i + 1];
        else if (buf[i] == 3) buf[i] = 0, ++buf[i + 1];
    }
    if (buf[len]) {
        if (sign > 0) {
            printf("%d", buf[len]);
        } else {
            putchar('Z');
        }
    }
    for (int i = len - 1; i >= 0; --i) {
        if (buf[i] == 0 || buf[i] == 2) printf("%d", buf[i]);
        else if (buf[i] == 1) {
            if (sign > 0) {
                printf("%d", buf[i]);
            } else {
                putchar('Z');
            }
        }
        else if (buf[i] == -1) {
            if (sign < 0) {
                putchar('1');
            } else {
                putchar('Z');
            }            
        }
    }
    puts("");

}

void Demical(const char *str) {
    int len = strlen(str);
    for (char *p = str; *p; ++p) {
        if (*p != 'Z' && *p != '1' && *p != '0') {
            puts("Radix Error");
            return;
        }
    }
    long long res = 0, base = 1, x;
    for (int i = len - 1; i >= 0; --i) {
        if (str[i] == '1') x = 1;
        else if (str[i] == '0') x = 0;
        else if (str[i] == 'Z') x = -1;
        res += base * x;
        base = base * 3;
    }
    printf("%lld %s\n", res, str);
}

int checkTer(const char *str) {
    char *p = str;
    if (*p != '-' && !isdigit(*p)) return 0;
    for (p = str + 1; *p; ++p) {
        if (!isdigit(*p)) return 0;
    }   
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s %s", comd, str);
        if (comd[0] == 'd') { // to ternary
            if (!checkTer(str)) {
                puts("Radix Error");
                continue;
            }
            LL x = atoll(str);
            Ternary(x);
        } else { // to demical
            Demical(str);
        }
    }
    return 0;
}