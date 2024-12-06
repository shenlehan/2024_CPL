#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *s1, *s2;
int T;

void mystrcat(char* s, char *t) {
    char *ans = calloc(1, 2005 * sizeof(char));
    int lens = strlen(s);

    for (int i = 0; i < lens; ++i) {
        char *tmp = strstr(t, s + i);
        if (tmp == t) { // tmp must be in the head
            strcat(ans, s);
            strcat(ans, t + lens - i);
            printf("%s\n", ans);
            free(ans);
            return;
        }
    }

    strcat(ans, s);
    strcat(ans, t);
    printf("%s\n", ans);
    free(ans);
    return; // remember to handle the case with no answer!
}

int main() {
    scanf("%d", &T);
    s1 = calloc(1, 1005 * sizeof(char)); // don't forget sizeof(char)
    s2 = calloc(1, 1005 * sizeof(char)); 
    while (T--) {
        scanf("%s %s", s1, s2);
        mystrcat(s1, s2);
    }
    free(s1); // don't forget to free s1, s2
    free(s2);
    return 0;
}