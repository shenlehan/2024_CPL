#include <stdio.h>
#include <string.h>
#define N 1005

int a, b, c, cura, curb, curc, len;
int x1, x2, y1, y2;
char op[N];

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    scanf("%d %d %d %s", &a, &b, &c, op);
    len = strlen(op);
    cura = a, curb = b, curc = c;
    x1 = y1 = 0, x2 = a, y2 = b;
    for (int i = 0; i < len; ++i) {
        if (op[i] == 'W') {
            x2 = x1;
            x1 = x1 - curc;
            swap(&cura, &curc);
        } else if (op[i] == 'A') {
            y2 = y1;
            y1 = y1 - curc;
            swap(&curb, &curc);
        } else if (op[i] == 'D') {
            y1 = y2;
            y2 = y2 + curc;
            swap(&curb, &curc);            
        } else {
            x1 = x2;
            x2 = x2 + curc;
            swap(&cura, &curc);            
        }
    }
    printf("%d %d %d %d\n", x1, x2, y1, y2);
    return 0;
}