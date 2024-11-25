#include <stdio.h>
#include <string.h>

char buf[100005];
char tmp[100004];
int wordcnt = 0;
char word[1000][100];

int main() {
    int k, flag = 0;
    while (scanf("%s", tmp) != EOF) {
        for (k = 0; k < strlen(tmp); ++k) {
            if (tmp[k] == ';') {
                flag = 1;
                break;
            }
        }
        if (flag) {
            memcpy(word[++wordcnt], tmp, sizeof(char) * k);
            if (k != strlen(tmp) - 1) {
                memcpy(word[++wordcnt], tmp + k + 1, sizeof(char) * (strlen(tmp) - k - 1));
            }
        } else {
            strcpy(word[++wordcnt], tmp);
        }
    }
    return 0;
}