#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *s1, *s2;
int T;

void build(char *des, char *s, char *t, int p) {
    int len = 0;
    for (int i = 0; i < p; ++i, ++len) {
        *(des + len) = *(s + i);
    }
    for (int i = 0; i < strlen(t); ++i, ++len) {
        *(des + len) = *(t + i);
    }
    *(des + len) = '\0';
}

char* mystrcat(char* s, char *t) {
    char *ans = calloc(1, 2005 * sizeof(char));
    int lens = strlen(s), lent = strlen(t);

    for (int ps = 0; ps < lens; ++ps) {
        int k = 0, pt = 0;
        for (k = ps; k < lens && pt < lent; ++pt, ++k) {
            if (*(s + k) != *(t + pt)) {
                break;
            }
        }
        if (k == lens) {
            build(ans, s, t, ps);
            return ans;
        }
    }

    build(ans, s, t, strlen(s));
    return ans; // remember to handle the case with no answer!
}

int main() {
    scanf("%d", &T);
    s1 = calloc(1, 1005 * sizeof(char)); // don't forget sizeof(char)
    s2 = calloc(1, 1005 * sizeof(char)); 
    while (T--) {
        scanf("%s %s", s1, s2);
        printf("%s\n", mystrcat(s1, s2));
    }
    free(s1); // don't forget to free s1, s2
    free(s2);
    return 0;
}