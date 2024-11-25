#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char rule[150], name[150];
char argu[105][10005];
int cnt;
int need[150];

void explain() {
    for (int i = 0; i < strlen(rule); ++i) {
        if (rule[i] == ':') {
            need[rule[i - 1]] = 1; // need
        } else {
            need[rule[i]] = 2; // don't need
        }
    }
}

int main() {
    // freopen("parse.in", "r", stdin);
    scanf("%s %s", rule, name);
    explain();
    while (scanf("%s", argu[cnt++]) != EOF);
    --cnt;
    printf("%s", name);
    // printf("cnt = %d\n", cnt);
    for (int i = 0; i < cnt; ++i) {
        if (argu[i][0] == '-') {
            if (!need[argu[i][1]]) {
                printf(": invalid option -- '%c'", argu[i][1]);
                return 0;
            } else if (need[argu[i][1]] == 1) {
                if (i == cnt - 1) {
                    printf(": option requires an argument -- '%c'", argu[i][1]);
                    return 0;
                }
                ++i;
            } else {
                continue;
            }
        }
    }
    puts("");
    int i = 0;
    while (i < cnt) {
        while (argu[i][0] != '-' && i < cnt)
            ++i;
        if (i >= cnt) {
            break;
        }
        if (need[argu[i][1]] == 1) {
            printf("%c=%s\n", argu[i][1], argu[i + 1]);
            i += 2;
        } else {
            printf("%c\n", argu[i][1]);
            i++;
        }
        
    }
    return 0;
}