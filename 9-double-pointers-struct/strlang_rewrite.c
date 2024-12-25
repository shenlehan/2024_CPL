#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int n;
char rule[405][10005];
char *pos[405][2];
char str[50000005];
char buf[50000005];
int len[405][2];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", rule[i]);
        pos[i][0] = strchr(rule[i], '[') + 1;
        pos[i][1] = strchr(pos[i][0] + 1, '[') + 1;
        char *x = strchr(rule[i], ']');
        *x = 0;
        x = strchr(pos[i][1], ']');
        *x = 0;
        len[i][0] = strlen(pos[i][0]);
        len[i][1] = strlen(pos[i][1]);
    }
    scanf("%s", str);

#if 0
    for (int i = 0; i < n; ++i) {
        printf("##%s##%s##\n", pos[i][0], pos[i][1]);
    }
#endif

#if 1    
    while (1) {
        int ok = 0;
        for (int cur = 0; cur < n; ++cur) {
            char op1 = *(pos[cur][0] - 2);
            char op2 = *(pos[cur][1] - 2);
            char *tmp = strstr(str, pos[cur][0]);
            // printf("cur = %d, op1 = %c, op2 = %c\n",cur, op1, op2);
            if (tmp == NULL) {
                // log("Not found!");
                continue;
            }

            if (op1 == '^') {
                if (tmp != str) {
                    continue;
                }
            }

            if (op1 == '$') {
                int lens = strlen(str);
                while (tmp + len[cur][0] != str + lens && tmp) {
                    tmp = strstr(tmp + 1, pos[cur][0]);
                }
                if (tmp == NULL) {
                    continue;
                }
            }
            // log("OK, cur = %d", cur);
            if (op2 == '.') {
                memmove(tmp + len[cur][1], tmp + len[cur][0], strlen(tmp + len[cur][0]) + 1);
                memcpy(tmp, pos[cur][1], len[cur][1]);
            } else if (op2 == '^') {
                strcpy(buf, pos[cur][1]);
                memcpy(buf + len[cur][1], str, tmp - str);
                *(buf + len[cur][1] + (tmp - str)) = 0;
                strcat(buf, tmp + len[cur][0]);
                strcpy(str, buf);
            } else {
                memmove(tmp, tmp + len[cur][0], strlen(tmp + len[cur][0]) + 1);
                strcat(str, pos[cur][1]);
            }
            ok = 1;
            break;

        }
        // printf("Now str = %s\n", str);
        if (!ok) {
            break;
        }
    }
#endif
    puts(str);
    return 0;
}