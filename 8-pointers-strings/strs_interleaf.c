#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

int T, ds1, ds2, lens1, lens2, size;
char *s1, *s2, ch;

void interleaveString(char *s, char *t) {
    char *ans = malloc(2005 * sizeof(char));
    int lens = strlen(s), lent = strlen(t);
    int ps = 0, pt = 0, pans = 0;
    int sover = 0, tover = 0;

    while (pans < size) {
        for (int i = 0; i < ds1; ++i) {
            if (ps + i < lens && pans < size) {
                *(ans + pans) = *(s + ps + i);
                ++pans;
            } else {
                break;
            }
        }
        ps += ds1;
        if (ps >= lens1)
            sover = 1;

        for (int i = 0; i < ds2; ++i) {
            if (pt + i < lent && pans < size) {
                *(ans + pans) = *(t + pt + i);
                ++pans;
            } else {
                break;
            }
        }
        pt += ds2;
        if (pt >= lens2)
            tover = 1;

        if (sover || tover)
            break;  
    }

    if (sover) {
        while (pans < size && pt < lent) {
            *(ans + pans) = *(t + pt);
            ++pans, ++pt;
        }
    } else if (tover) {
        while (pans < size && ps < lens) {
            *(ans + pans) = *(s + ps);
            ++pans, ++ps;
        }        
    }
    *(ans + pans) = '\0';

    if (strlen(ans) == size) {
        *(ans + (pans - 1)) = '\0';
    }
    // printf("Now length: %d ", strlen(ans));
    puts(ans);
}

int main() {
    scanf("%d", &T);
    s1 = malloc(2005 * sizeof(char));
    s2 = malloc(2005 * sizeof(char));
    getchar();

    while (T--) {
        lens1 = lens2 = 0;
        while ((ch = getchar()) != ';') {
            *(s1 + lens1) = ch;
            ++lens1;
        }
        *(s1 + lens1) = '\0';
        while ((ch = getchar()) != ';') {
            *(s2 + lens2) = ch;
            ++lens2;
        }        
        *(s2 + lens2) = '\0';

        scanf("%d;%d;%d", &ds1, &ds2, &size);
        getchar();
        // printf("Now size: %d\n", size);
        // printf("s1 = %s, s2 = %s, ds1 = %d, ds2 = %d, size = %d\n", s1, s2, ds1, ds2, size);

        interleaveString(s1, s2);
    }

    free(s1);
    free(s2);

    return 0;
}