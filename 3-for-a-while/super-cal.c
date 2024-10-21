#pragma GCC optimize(2)
#include <stdio.h>
#include <string.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

char a[10005], b[10005], op;
int c[10005], a1[10005], b1[10005];
int lena, lenb, lenc;

int cmp() {
    if (lena > lenb) { // a > b
        return 1;
    }
    if (lena < lenb) { // a < b
        return -1;
    }
    if (lena == lenb) {
        for (int i = lena - 1; i >= 0; --i) {
            if (a1[i] < b1[i]) {
                return -1;
            } else if (a1[i] > b1[i]) {
                return 1;
            }
        }
    }
    return 0; // equal
}

void init() {
    lena = strlen(a);
    lenb = strlen(b);

    for (int i = 0; i < lena; ++i)
        a1[i] = a[lena - i - 1] - '0';

    for (int i = 0; i < lenb; ++i)
        b1[i] = b[lenb - i - 1] - '0';    

}

void add() {
    lenc = max(lena, lenb) + 1;
    for (int i = 0, up = 0; i < lenc; ++i) {
        c[i] = a1[i] + b1[i] + up;
        up = 0;
        if (c[i] >= 10) {
            up = 1;
            c[i] = c[i] % 10;
        }
    }
}

void sub() {
    int t = cmp();
    lenc = max(lena, lenb) + 1;
    if (t > 0) {
        for (int i = 0, up = 0; i < lenc; ++i) {
            c[i] = a1[i] - b1[i] - up;
            up = 0;
            if (c[i] < 0) {
                up = 1;
                c[i] = c[i] + 10;
            }
        }
    } else if (t < 0){
        for (int i = 0, up = 0; i < lenc; ++i) {
            c[i] = b1[i] - a1[i] - up;
            up = 0;
            if (c[i] < 0) {
                up = 1;
                c[i] = c[i] + 10;
            }
        }
        c[lenc] = -1;
    } else {
        lenc = 1;
    }
}

void mul() {
    
}

void print() {
    if (c[lenc] == -1) {
        putchar('-');
        --lenc;
    }

    while (c[lenc] == 0)
        --lenc;

    for (int i = lenc; i >= 0; --i) {
        printf("%d", c[i]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        for (int i = 0; i < 10005; ++i)
            a1[i] = b1[i] = c[i] = 0,
            a[i] = b[i] = 0;

        scanf("%s %c %s", a, &op, b);
        init();

        if (op == '+') {
            add();
            print();
        } else if (op == '-') {
            sub();
            print();
        }


        puts("");
    }
    return 0;
}