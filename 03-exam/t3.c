#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

char tmp[1000005];
char res[1000005];
char input[50000005];

int n, len1[405], len2[405];
char op1[405], op2[405];
char str1[405][500005], str2[405][500005];
char buf[5000005];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", tmp);
        op1[i] = tmp[0];
        int len = 0;
        char *p;
        for (p = tmp + 2; *p != ']'; ++p) {
            str1[i][len++] = *p;
        }
        str1[i][len] = 0;
        len1[i] = len;

        len = 0;
        op2[i] = *(p + 1);
        for (p += 3; *p != ']'; ++p) {
            str2[i][len++] = *p;
        }        
        str2[i][len] = 0;
        len2[i] = len;
    }
    scanf("%s", input);

    while (1) {
        int f = 0;
        // log("");
        for (int i = 0; i < n; ++i) {
            // printf("#####%d#####\n", i);
            char *pos = strstr(input, str1[i]);
            if (pos == NULL) {
                continue;
            }
            memset(buf, 0, sizeof(buf));
            if (op1[i] == '^' && pos != input) {
                continue;
            }

            int t =0 ;
            while (op1[i] == '$' && pos + len1[i] != input + strlen(input)) {
                pos = strstr(pos + 1, str1[i]);
                // printf("%d\n", pos + len1[i] - input);
                if (pos == NULL) {
                    t = 1;
                    break;
                }
            }
            if (t) continue;
            
            f = 1;
            // log("input = %s", input);
            if (op2[i] == '.') {
                int len = 0;
                for (char *s = pos + len1[i]; *s; ++s) {
                    buf[len++] = *s;
                }
                buf[len] = 0;

                *pos = 0;
                strcat(input, str2[i]);
                strcat(input, buf);

            } else if (op2[i] == '$') {
                int len = 0;
                for (char *s = pos + len1[i]; *s; ++s) {
                    buf[len++] = *s;
                }
                buf[len] = 0;
                *pos = 0;
                strcat(input, buf);
                strcat(input, str2[i]);
            } else {
                int len = 0;
                for (char *s = pos + len1[i]; *s; ++s) {
                    buf[len++] = *s;
                }
                buf[len] = 0;
                *pos = 0;
                strcpy(res, str2[i]);
                strcat(res, input);
                strcat(res, buf);
                strcpy(input, res);
            }
            // log("input = %s", input);
            break;                      
        }
        if (!f) {
            break;
        }
    }

    printf("%s", input);
    return 0;
}