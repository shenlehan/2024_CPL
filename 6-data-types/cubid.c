#include <stdio.h>
#define N 

int T, a, b, c;
char m[200][200];

void print() {
    for (int i = 0; i < 2 * b + 2 * c + 1; ++i) {
        for (int j = 0; j < 2 * a + 2 * b + 1; ++j) {
            printf("%c", m[i][j]);
        }
        puts("");
    }
}

int main() {
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d %d", &a, &b, &c);
        for (int i = 0; i < 200; ++i) {
            for (int j = 0; j < 200; ++j) {
                m[i][j] = ' ';
            }
        }

        for (int i = 0; i < 2 * b; i += 2) {
            for (int j = 2 * b - i; j < 2 * a + 2 * b + 1 - i; ++j) {
                m[i][j] = (j % 2 == 0) ? '+' : '-';
            }
        }

        for (int i = 1; i < 2 * b; i += 2) {
            for (int j = 2 * b - i; j < 2 * a + 2 * b + 1 - i; ++j) {
                m[i][j] = (j % 2 == 0) ? ' ' : '/';
            }
        }

        for (int i = 2 * b; i < 2 * c + 1 + 2 * b; ++i) {
            for (int j = 0; j < 2 * a + 1; ++j) {
                if (i % 2 == 0) {
                    m[i][j] = (j % 2 == 0) ? '+' : '-';
                } else {
                    m[i][j] = (j % 2 == 0) ? '|' : ' ';
                }
            }
        }

        for (int j = 2 * a + 1; j < 2 * a + 2 * b + 1; ++j) {
            for (int i = 2 * b + 1 - (j - (2 * a + 1)); i < 2 * b + 2 * c + 1 - (j - (2 * a + 1)); ++i) {
                if (j % 2 != 0) {   
                    m[i][j] = (i % 2 == 0) ? ' ' : '/';
                } else {
                    m[i - 1][j] = (i % 2 == 0) ? '|' : '+';
                }
            }
        }

        print();
        
    }

    return 0;
}