#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int s[100005], T, top;
char str[100005];

int isleft(char ch) {
    return (ch == '(') || (ch == '[') || (ch == '{');
}

int match(char ch) {
    if (top == 0)
        return 0; // remember to judge non-empty!
    if (ch == ')') {
        return s[top - 1] == '(';
    } else if (ch == ']') {
        return s[top - 1] == '[';
    } else if (ch == '}') {
        return s[top - 1] == '{';
    }
}

int main() {
    scanf("%d", &T);

    while (T--) {
        scanf("%s", str);
        int f = 0;
        top = 0;
        for (char *p = str; *p; ++p) {
            if (isleft(*p)) {
                s[top++] = *p;
            } else {
                if (match(*p)) {
                    --top;
                } else {
                    puts("False");
                    f = 1;
                    break;
                }
            }
        }
        if (!f) {
            puts(!top ? "True" : "False");
        }
    }

    return 0;
}