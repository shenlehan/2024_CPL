#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 100005

int T, len, stdlen;
int vis[1005];
char input[N], ans[N], std[N];

void getStandard(char *str, char *res, int len, int* stdlen) {
    int m = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '?' && str[len - i + 1] != '?') {
            str[i] = str[len - i + 1];
        }
    }

    for (int i = 0; i < len; i++) {
        if (str[i] != '?')
            res[m++] = str[i];
        else
            res[m++] = '*', res[m++] = '*';
    }

    *stdlen = m;
}

int pali(char *s2) {
    int len = strlen(s2);
    for (int i = 0; i < len; ++i) {
        if (s2[i] != s2[stdlen - i - 1]) {
            // printf("%d\n", __LINE__);
            return 0;
        }
    }
    return 1;
}

int compare(char *s1, const char *s2) {
    if (strlen(s1) != strlen(s2)) return 0;
    if (!pali(s2)) return 0;

    char x = 0, y = 0;
    for (int i = 0; i < stdlen; ++i) {
        if (s1[i] != '*') {
            if (s2[i] != s1[i]) return 0;
        } else {

            if (x == 0) {
                x = s2[i];
                continue;
            }
            y = s2[i];
            if ((!isdigit(x)) || (!isdigit(y))) return 0;
            if (x == y) {
                int t = (x - '0') * 10 + (y - '0');
                if (vis[t] == 2) return 0;
                vis[t]++;
                x = y = 0;
                continue;
            }
            int t1 = (x - '0') * 10 + (y - '0');
            int t2 = (y - '0') * 10 + (x - '0');
            if (vis[t1] == 2 && vis[t2] == 2) {
                return 0;
            }
            if (vis[t2] < 2) {
                vis[t2] += 1;
            } else {
                vis[t1] += 1;
                // printf("%d\n", __LINE__);
            }
            x = y = 0;
        }

    }

    return 1;
}

int main() {
    scanf("%d", &T);
    
    while (T--) {
        memset(vis, 0, sizeof(int) * 105);
        scanf("%d %s %s", &len, input, ans);
        getStandard(input, std, len, &stdlen);
        // printf("%s %d\n", std, stdlen);
        printf("%s\n", compare(std, ans) ? "Correct." : "Wrong Answer!");
    }

    return 0;
}