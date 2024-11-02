#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

char num[50], str[50];
int tmp[30];
int n;

int main() {
    scanf("%d ", &n);
    
    while (n--) {
        int x = 0;
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
        printf("String is: %s\n", str);


        int sgn = 1;
        if (str[0] == '-') {
            int fac = 1;
            sgn = -1;
            log("");
            for (int i = length - 1; i > 0; --i) {
                x += fac * (str[i] - '0');
                fac *= 10;
            }
        } else {
            log("");
            int fac = 1;
            for (int i = length - 1; i >= 0; --i) {
                log("");
                x += fac * (str[i] - '0');
                fac *= 10;
            }            
        }

        printf("%d\n", x);


    }

    return 0;
}