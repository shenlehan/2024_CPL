#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define ll long long
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

static char *ones[] = {
  "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
  "ten", "eleven", "twelve", "thirteen", "fourteen",
  "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

static char *tens[] = {
  "0", "1", "twenty", "thirty", "forty", 
  "fifty", "sixty", "seventy", "eighty", "ninety"};

int Num;
ll num;

void print(ll x) {
    int f1 = 0, f2 = 0;
    if (x >= 100) {
        printf("%s hundred ", ones[x / 100]);
        x %= 100;
        f1 = 1;
    }

    if (10 <= x && x <= 19) {
        if (f1) printf("and ");
        printf("%s ", ones[x]);
    } else if (x >= 20) {
        if (f1) printf("and ");
        printf("%s", tens[x / 10]);
        x %= 10;
        if (x) {
            printf("-%s ", ones[x]);
        } else {
            putchar(' ');
        }
    } else if (x) {
        if (f1) printf("and ");
        printf("%s ", ones[x]);
    }
}

int main() {
    scanf("%d", &Num);
    num = (ll)Num;
    if (num < 0) {
        num = -num;
        printf("minus ");
    } else if (num == 0) {
        puts("zero");
        return 0;
    }
    // printf("%lld\n", num);
    if (num >= 1000000000) {
        print(num / 1000000000);
        printf("billion ");
        num %= 1000000000;
    }
    if (num >= 1000000) {
        print(num / 1000000);
        printf("million ");
        num %= 1000000;
    }
    if (num >= 1000) {
        print(num / 1000);
        printf("thousand ");
        num %= 1000;
    }
    print(num);

    return 0;
}