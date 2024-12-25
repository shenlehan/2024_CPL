#include <stdio.h>

int MyStrlen1(const char *s) { // return actual len + 1
    int len = 0;
    while (s[len++] != '\0');
    return len;
}

size_t MyStrlen2(const char *s) { // return actual len
    const char *p;
    for (p = s; *p != '\0'; ++p);
    return p - s;
}

int main() {
    char *str = "Hello!";
    char _str[] = {'H', 'E', 'L', 'L', 'O', '!'};
    printf("%d\n", MyStrlen1(str));
    printf("%d", MyStrlen2(str));
    return 0;
}