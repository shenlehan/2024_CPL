#include <stdio.h>

void MyStrcpy1(char *des, const char *src) {
    while (*src) *(des++) = *(src++);
    *des = '\0';
}

int main() {
    char str1[] = "Hello";
    char str2[] = "World!";
    char str3[10];
    MyStrcpy1(str3, str1);
    printf("%s", str3);
    return 0;
}