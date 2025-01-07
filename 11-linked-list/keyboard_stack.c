#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 2000005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); printf("\n"); } while(0)

typedef struct Node {
    char ch;
    int id;
} Node;

Node upper[N], lower[N];
int top1, top2, q, k, cnt, outp;
char str[N], output[N];

void query(int pos) {
    int p1 = top1, p2 = top2;
    outp = 0;
    while (pos--) {
        if (upper[p1].id > lower[p2].id) {
            // log("upper[p1].id=%d,lower.id=%d",upper[p1].id,lower[p2].id);
            output[outp++] = upper[p1--].ch;
            // log("out[i]=%c",output[outp - 1]);
        } else {
            // log("upper[p1].id=%d,lower.id=%d",upper[p1].id,lower[p2].id);
            output[outp++] = lower[p2--].ch;
            // log("out[i]=%c",output[outp - 1]);
        }
    }
    for (int i = outp - 1; i >= 0; --i) putchar(output[i]);
    puts("");
}

void print() {
    for (int i = 1; i <= top1; ++i) {
        printf("(%c,%d)->", upper[i].ch, upper[i].id);
    }
    puts("");
    for (int i = 1; i <= top2; ++i) {
        printf("(%c,%d)->", lower[i].ch, lower[i].id);
    }
    puts("");
}

void insert(const char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if (s[i] == 'M') {
            if (top1 >= 1) --top1; 
        } else if (s[i] == 'm') {
            if (top2 >= 1) --top2;
        } else {
            if (isupper(s[i])) {
                top1++;
                upper[top1].ch = s[i];
                upper[top1].id = ++cnt;
            } else {
                ++top2;
                lower[top2].ch = s[i];
                lower[top2].id = ++cnt;
            }
        }
    }
}

int main() {
    freopen("keyboard.txt", "r", stdin);
    scanf("%d", &q);

    while (q--) {
        scanf("%s", str);
        if (str[0] == '?') {
            scanf("%d", &k);
            // log("k=%d",k);
            query(k);
        } else {
            // log("str=%s",str);
            insert(str);
        }
    }
    return 0;
}