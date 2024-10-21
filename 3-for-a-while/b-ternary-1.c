#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef long long ll;

char num[50], str[50];
int tmp[30];
int n;

int main() {
    scanf("%d ", &n);
    
    while (n--) {
        ll x = 0;
        scanf("%s", str);

        int f = 0, length = strlen(str);
        for (int i = 0; i < length; ++i) {
            if (!(isdigit(str[i]) || str[i] == '-')) {
                puts("Radix Error");
                f = 1;
                break;
            }
        }
        if (f)
            continue;

        int sgn = 1;
        if (str[0] == '-') {
            ll fac = 1;
            sgn = -1;
            for (int i = length - 1; i > 0; --i) {
                x += fac * (str[i] - '0');
                fac *= 10;
            }
        } else {
            ll fac = 1;
            for (int i = length - 1; i >= 0; --i) {
                x += fac * (str[i] - '0');
                fac *= 10;
            }            
        }

        if (x < 0) {
            x = -x;
        }

        if (str[0] == '0') {
            printf("0\n");
            continue;
        }

        int t = 0, len = 0;

        while (x) {
            tmp[t++] = x % 3;
            x /= 3;
        }

        for (int i = 0; i < 50; ++i)
            num[i] = '0';

        for (int i = 0; i < t; ++i) {
            num[i] += tmp[i];
        }

        for (int i = 0; ; ++i) {
            ++len;
            if (num[i] == '2') {
                num[i] = 'Z';
                num[i + 1]++;
            } else if (num[i] == '3') {
                num[i] = '0';
                num[i + 1]++;
            }

            if (i >= t && num[i] == '0' && num[i + 1] == '0')
                break;
        }

        if (sgn > 0) 
            for (int i = len - 2; i >= 0; --i)
                putchar(num[i]);
        else {
            for (int i = 0; i < len; ++i) {
                if (num[i] == '1')
                    num[i] = 'Z';
                else if (num[i] == 'Z')
                    num[i] = '1';
            }
            for (int i = len - 2; i >= 0; --i)
                putchar(num[i]);
        }
        puts(""); 

    }

    return 0;
}