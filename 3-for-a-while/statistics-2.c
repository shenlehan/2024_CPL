#include <stdio.h>
#include <stdlib.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define log(f, args...) do { printf("%d, %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0);

int bucket[128 + 10], n, tot, max_height;
char map[10005][128], str[10000 + 5];

int main() {
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; ++i) {
        str[i] = getchar();
    }

    for (int i = 0; i < n; ++i) {
        bucket[(int)str[i]]++;
    }

    for (int i = 0; i < 1000; ++i)
        for (int j = 0; j < 128; ++j)
            map[i][j] = ' ';

    for (int i = 'a'; i <= 'z'; ++i) {
        max_height = max(max_height, bucket[i]);
        max_height = max(max_height, bucket[i - 'a' + 'A']);
    }
    
    int first = 0;
    for (int i = 'a'; i <= 'z'; ) {

        if (first) {
            map[max_height][tot] = '-';
            tot++;    
        }

        if (bucket[i]) {
            for (int t = 0; t < bucket[i]; ++t) {
                map[max_height - t - 1][tot] = '=';
            }
            map[max_height][tot] = '-';
            map[max_height + 1][tot] = i;
            tot++;
            first = 1;
        }

        if (bucket[i - 'a' + 'A']) {
            for (int t = 0; t < bucket[i - 'a' + 'A']; ++t) {
                map[max_height - t - 1][tot] = '=';
            }
            map[max_height][tot] = '-';
            map[max_height + 1][tot] = i - 'a' + 'A';
            tot++;
            first = 1;
        }
        
        ++i;
        for (; !bucket[i] && !bucket[i - 'a' + 'A']; ++i);

    }

    for (int j = 0; j <= max_height + 1; ++j) {
        for (int i = 0; i < tot; ++i) {
            printf("%c", map[j][i]);
        }
        puts("");
    }

    return 0;
}