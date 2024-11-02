#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 25

const int thousand = 1000;
const int million = 1000000;
const int billion = 1000000000;

static char *ones[25] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};

static char *tens[25] = {
    "0", "1", "twenty", "thirty", "forty", 
    "fifty", "sixty", "seventy", "eighty", "ninety"
};

long long n;

void get_billion(long long x) {
    if (x >= billion) {
        int t1 = x / billion;
        printf("%s billion ", ones[t1]);
    }
}

void get_million(long long x) {
    if (x >= million) {
        int t1 = x / million;
        printf("%s million ", ones[t1]);
    }    
}

void get_hundred(int x) {
    int hun = x / 100;
    printf("%s hundred ", ones[hun]);
    x %= 100;
    if (x < 20 && x != 0) {
        printf("and %s ", ones[x]);
    } else if (x != 0 && x % 10 != 0) {
        printf("and %s-%s ", tens[x / 10], ones[x % 10]);
    } else if (x % 10 == 0 && x != 0) {
        printf("and %s ", tens[x / 10]);
    }
}

int main() {
    scanf("%lld", &n);
    if (n < 0) {
        printf("minus ");
        n *= -1;
    }
    if (n == 0) {
        puts("zero");
        return 0;
    }

    if (n >= billion) {
        get_billion(n);
        n %= billion;
    }

    if (n >= million) {
        int t1 = n / million;
        n %= million;
        if (t1 >= 100) {
            get_hundred(t1);
        } else {
            if (t1 < 20 && t1 != 0) {
                printf("%s ", ones[t1]);
            } else if (t1 != 0 && t1 % 10 != 0) {
                printf("%s-%s ", tens[t1 / 10], ones[t1 % 10]);
            } else if (t1 % 10 == 0 && t1 != 0) {
                printf("%s ", tens[t1 / 10]);
            }
        }
        printf("million ");
    }

    if (n >= thousand) {
        int t1 = n / thousand;
        n %= thousand;
        if (t1 >= 100) {
            get_hundred(t1);
        } else {
            if (t1 < 20 && t1 != 0) {
                printf("%s ", ones[t1]);
            } else if (t1 != 0 && t1 % 10 != 0) {
                printf("%s-%s ", tens[t1 / 10], ones[t1 % 10]);
            } else if (t1 % 10 == 0 && t1 != 0) {
                printf("%s ", tens[t1 / 10]);
            }
        }
        printf("thousand ");
    }

    if (n >= 100) {
        get_hundred(n);
    } else if (n != 0 && n < 20) {
        printf("%s ", ones[n]);
    } else if (n != 0 && n % 10 != 0) {
        printf("%s-%s ", tens[n / 10], ones[n % 10]);
    } else if (n != 0) {
        printf("%s ", tens[n / 10]);
    }

    return 0;
}