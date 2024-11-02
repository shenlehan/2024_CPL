#include <stdio.h>

int n;

char num1[25][15] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};

char num2[10][15] = {
    "0", "1", "twenty", "thirty", "fourty", "fifty", "sixty",
    "seventy", "eighty", "ninety"
};

int main() {
    scanf("%d", &n);
    if (n < 20) {
        printf("%s", num1[n]);
    } else if (n < 100) {
        if (n % 10 != 0)
            printf("%s-%s", num2[n / 10], num1[n % 10]);
        else
            printf("%s", num2[n / 10]);
    } else {
        int hun = n / 100;
        printf("%s hundred", num1[hun]);
        n %= 100;
        if (n < 20 && n != 0) {
            printf(" and %s", num1[n]);
        } else if (n != 0 && n % 10 != 0) {
            printf(" and %s-%s", num2[n / 10], num1[n % 10]);
        } else if (n % 10 == 0 && n != 0) {
            printf(" and %s", num2[n / 10]);
        }
    }
    return 0;
}