#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

char command[1005], name[1005], para[1005], ans[40005], res[40005];
int wait_para = 0;

int main() {
    freopen("parse.in", "r", stdin);
    scanf("%s %s", command, name);
    sprintf(ans, "%s\n", name);
    while (~scanf("%s", para)) {
        if (para[0] == '-') {
            char *tmp = strchr(command, para[1]);
            char op = para[1];
            if (tmp != NULL) {
                if (*(tmp + 1) == ':') {
                    if (~scanf("%s", para)) {
                        sprintf(res, "%c=%s\n", op, para);
                        strcat(ans, res);
                    } else {
                        printf("%s: option requires an argument -- '%c'", name, op);
                        return 0;
                    }
                } else {
                    sprintf(res, "%c\n", op);
                    strcat(ans, res);
                }
            } else {
                printf("%s: invalid option -- '%c'", name, para[1]);
                return 0;
            }
        }
    }
    printf("%s", ans);
    return 0;
}