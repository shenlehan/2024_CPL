#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *s, *t;

int main() {
    s = malloc(100005 * sizeof(char));
    t = malloc(100005 * sizeof(char));
    scanf("%s %s", s, t);
    int ps = 0, pt = 0, lens = strlen(s), lent = strlen(t);
    while (ps < lens) {
        pt = 0;
        int k = ps;
        while (*(s + k) == *(t + pt) && pt < lent) {
            ++pt;
            ++k;
        }
        if (pt == lent) {
            printf("%d ", ps);
        }
        ++ps;
    }
    return 0;
}