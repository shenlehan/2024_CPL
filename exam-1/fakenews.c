#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char buf[1050];

bool is_captal(char ch) {
    return 'A' <= ch && ch <= 'Z';
}

int main() {
    scanf("%s", buf);
    int len = strlen(buf);
    int p = 0;
    for (; ; ) {
        if (is_captal(buf[p])) {
            if (p == 0) 
                putchar(buf[p]);
            else {
                putchar(' ');
                putchar(buf[p] - 'A' + 'a');
            } 
        } else {
            putchar(buf[p]);
        }
        ++p;
        if (p == len) {
            break;
        }
    }

    return 0;
}