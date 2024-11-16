#pragma GCC optimize(2)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000005

char str[N], s[N];
int T, len, top, flag;

int isleft(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

int match(char c1, char c2) {
    if (c1 == '(' && c2 == ')')
        return 1;
    if (c1 == '[' && c2 == ']')
        return 1;
    if (c1 == '{' && c2 == '}')
        return 1;
    return 0;
}
int main() {
    scanf("%d", &T);

    while (T--) {
        scanf("%s", str);
        len = strlen(str);
        flag = top = 0;

        for (int i = 0; i < len; ++i) {
            if (isleft(str[i])) {
                s[top++] = str[i];
            } else {
                if (top > 0 && match(s[top - 1], str[i])) {
                    --top;
                } else {
                    flag = 1;
                    break;
                }
            }
        }

        if (flag == 1 || top > 0) {
            puts("False");
        } else {
            puts("True");
        }
    }

    return 0;
}