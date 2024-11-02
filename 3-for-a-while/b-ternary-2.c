#include <stdio.h>
#include <string.h>

char num[20];
int n, len;

int calc(char ch) {
    if (ch == '1')
        return 1;
    else if (ch == '0')
        return 0;
    else 
        return -1;
}

int main() {
    scanf("%d", &n);

    while (n--) {
        scanf("%s", num);
        len = strlen(num);
        int f = 0;
        for (int i = 0; i < len; ++i) {
            if (num[i] != '0' && num[i] != '1' && num[i] != 'Z') {
                puts("Radix Error");
                f = 1;
                break;        
            }
        }

        if (f)
            continue;

        int sgn = 1;
        if (num[0] == 'Z') {
            sgn = -1;
            for (int i = 0; i < len; ++i) {
                if (num[i] == '1')
                    num[i] = 'Z';
                else if (num[i] == 'Z')
                    num[i] = '1';
            }
        }

        int res = 0, fac = 1;

        for (int i = len - 1; i >= 0; --i) {
            res += fac * calc(num[i]);
            fac *= 3;
        }

        printf("%d\n", res * sgn);

    }

    return 0;
}