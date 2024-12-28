#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 405

char op[N][3], str1[N][500005], str2[N][500005];
char output[50000005];
char ch;
int n, len1[N], len2[N];

int main() {
    scanf("%d", &n);
    getchar();
    for (int i = 1; i <= n; ++i) {
        op[i][1] = getchar();
        getchar();
        while ((ch = getchar()) != ']') str1[i][len1[i]++] = ch;
        str1[i][len1[i]] = 0;
        
        op[i][2] = getchar();
        getchar();
        while ((ch = getchar()) != ']') str2[i][len2[i]++] = ch;
        str2[i][len2[i]] = 0;

        getchar();
    }

    scanf("%s", output);
#if 0
    for (int i = 1; i <= n; ++i) {
        printf("op1 = %c, op2 = %c, str1 = %s, str2 = %s\n", op[i][1], op[i][2], str1[i], str2[i]);
    }
#endif

    while (1) {
        int worked = 0;
        for (int i = 1; i <= n; ++i) {
            char *pos1 = strstr(output, str1[i]);
            if (pos1 == NULL) continue;
            if (op[i][1] == '^') {
                if (pos1 != output) continue;
            }
            if (op[i][1] == '$') {
                int lenOut = strlen(output);
                int k, j;
                for (k = lenOut - 1, j = len1[i] - 1; j >= 0; --k, --j) {
                    // printf("%c %c\n", output[k], str1[i][j]);
                    if (output[k] != str1[i][j]) {
                        break;
                    }
                }
                if (j != -1) {
                    // puts("FAIL");
                    continue;
                }
                else pos1 = output + lenOut - len1[i];
            }

            worked = 1;
            int len = pos1 - output;
            
            if (op[i][2] == '.') {
                memmove(pos1 + len2[i], pos1 +len1[i], strlen(pos1 + len1[i]) + 1);
                memcpy(pos1, str2[i], len2[i]);
            } else if (op[i][2] == '^') {
                memmove(pos1, pos1 + len1[i], strlen(pos1 + len1[i]) + 1);
                memmove(output + len2[i], output, strlen(output) + 1);
                memcpy(output, str2[i], len2[i]);
            } else {
                memmove(pos1, pos1 + len1[i], strlen(pos1 + len1[i]) + 1);
                strcat(output, str2[i]);
            }
            // printf("i = %d, Cur output = %s\n", i, output);
            break;
        }
        if (!worked) break;

    }
    printf("%s", output);

    return 0;
}