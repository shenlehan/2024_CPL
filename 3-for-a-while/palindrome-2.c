#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, p, cnt;
char *str;
char *output;

char num[100][5];

int main() {
    scanf("%d", &n);
    str = malloc(n + 2);
    output = malloc(n + 200000);
    scanf("%s", str + 1);

    for (int i = 0; i <= 99; ++i) {
        if (i <= 9) {
            num[i][0] = '0';
            num[i][1] = i + '0';
        } else {
            num[i][0] = (int)(i / 10) + '0';
            num[i][1] = (int)(i % 10) + '0';
        }
    }


    // for (int i = 0; i <= 99; ++i) {
    //     putchar(num[i][0]);
    //     putchar(num[i][1]);
    //     putchar(' ');
    // }

    int mid = n >> 1;

    for (int i = 1; i <= mid; ++i) {
        if (str[i] == '?' && str[n - i + 1] == '?') {
            output[p++] = num[cnt][0],
            output[p++] = num[cnt][1];
            ++cnt;
        } else if (str[i] == '?' && str[n - i + 1] != '?') {
            output[p++] = str[n - i + 1];
        } else if (str[i] != '?' && str[n - i + 1] == '?') {
            output[p++] = str[i];
        } else {
            output[p++] = str[i];
        }
    }

    if (n % 2 == 1) {
        output[p++] = str[mid + 1];
    }

    output[p++] = '\0';
    if (n % 2 == 1) {
        printf("%s", output);
        for (int i = p - 3; i >= 0; --i) {
            putchar(output[i]);
        }
    } else {
        printf("%s", output);
        for (int i = p - 2; i >= 0; --i) {
            putchar(output[i]);
        }        
    }

    return 0;
}