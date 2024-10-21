#include <stdio.h>

char s[20 + 1];
int pre;
double frac, factor;
char unit;

int main() {
    scanf("%s%d%lf%lf %c", s, &pre, &frac, &factor, &unit);
    printf("%.2s: %d (%.5f) | %.5E %.5f %c", s, pre, frac, pre + frac, (pre + frac) * factor, unit - 'a' + 'A');
    return 0;
}