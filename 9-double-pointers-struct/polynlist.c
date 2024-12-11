#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

struct poly {
    int deg;
    int arg[10005];
} p1, p2;

char var[15];
int s, e;

void print(int maxpos, int i, int tmp) {
    if (!tmp)
        return;

    if (i == 0) {
        if (tmp > 0) 
            printf("+%d", tmp);
        else 
            printf("%d", tmp);
    } else if (i == maxpos) {
        if (tmp > 1)
            printf("%d%s^%d", tmp, var, i);
        
        else if (tmp == 1)
            printf("%s^%d", var, i);

        else if (tmp == -1) 
            printf("-%s^%d", var, i);

        else 
            printf("%d%s^%d", tmp, var, i);            
    } else if (i != 1) {
        if (tmp > 1)
            printf("+%d%s^%d", tmp, var, i);
        
        else if (tmp == 1)
            printf("+%s^%d", var, i);

        else if (tmp == -1) 
            printf("-%s^%d", var, i);

        else 
            printf("%d%s^%d", tmp, var, i);
    } else {
        if (tmp > 1)
            printf("+%d%s", tmp, var);
        
        else if (tmp == 1)
            printf("+%s", var);

        else if (tmp == -1) 
            printf("-%s", var);

        else 
            printf("%d%s", tmp, var);       
    }
}

int main() {
    freopen("2.in", "r", stdin);
    freopen("ans.out", "w", stdout);
    scanf("%d %d %s", &p1.deg, &p2.deg, var);
    for (int i = p1.deg; i >= 0; --i) {
        scanf("%d", &p1.arg[i]);
    }
    for (int i = p2.deg; i >= 0; --i) {
        scanf("%d", &p2.arg[i]);
    }
    
    s = max(p1.deg, p2.deg), e = min(p1.deg, p2.deg);

    // add
    for (int i = s; i >= 0; --i) {
        print(s, i, p1.arg[i] + p2.arg[i]);
    }    
    puts("");

    // minus
    for (int i = s; i >= 0; --i) {
        print(s, i, p1.arg[i] - p2.arg[i]);
    }  
    puts("");

    // mul
    for (int i = p1.deg + p2.deg; i >= 0; --i) {
        int num = 0;
        for (int j = 0; ; ++j) {
            if (i - j < 0) 
                break;
            num += p1.arg[j] * p2.arg[i - j];
        }
        print(p1.deg + p2.deg, i, num);
    }

    return 0;
}