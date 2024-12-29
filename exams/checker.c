#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 100005

int T, len, stdlen;
int vis[1005];
char input[N], ans[N], std[N];

void getStandard(const char *str, char *res, int len, int* stdlen) {
    int t = 0;
    for (int i = 0; i < len / 2; ++i) {
        if (str[i] != '?' && str[len - i - 1] != '?') {
            res[t++] = str[i];
            continue;
        } else if (str[i] == '?' && str[len - i - 1] == '?') {
            res[t++] = '*',
            res[t++] = '*';

        } else {
            if (str[i] != '?') {
                res[t++] = str[i];
            } else {
                res[i] = str[len - i - 1];
                res[t++] = str[len - i - 1];
            }
        }
    }

    if (len % 2 == 0) {
        int k = t;
        for (int i = t - 1; i >= 0; --i) {
            res[t++] = res[i];
        }
        res[t] = 0;
    } else {
        res[t++] = str[len / 2];
        int k = t;
        for (int i = t - 2; i >= 0; --i) {
            res[t++] = res[i];
        }
        res[t] = 0;
    }

    *stdlen = t;
}

int compare(char *s1, const char *s2) {
    if (strlen(s1) != strlen(s2)) return 0;
    
    for (int i = 0; i < stdlen; ++i) {
        if (s1[i] != '*') {
            if (s2[i] != s1[i]) return 0;
        } else {

            if ((!isdigit(s2[i])) || (!isdigit(s2[i + 1]))) return 0;

            int x = s2[i] - '0';
            x = x * 10 + s2[i + 1] - '0';
            int y = s2[i + 1] - '0';
            y = y * 10 + s2[i] - '0';
            ++i;

            if (x == y) {
                if (vis[x] == 2) {
                    // printf("%d\n", __LINE__);
                    return 0;
                }
                vis[x]++;
            } else {
                if (vis[x] == 2 && vis[y] == 2) {
                    return 0;
                }
                if (vis[y] < 2) {
                    vis[y] += 1;
                } else {
                    vis[x] += 1;
                    // printf("%d\n", __LINE__);
                    return 0;
                }
            }
        }
        if (s2[i] != s2[stdlen - i - 1]) {
            // printf("%d\n", __LINE__);
            return 0;
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
        printf("%s %d\n", std, stdlen);
        printf("%s\n", compare(std, ans) ? "Correct." : "Wrong Answer!");
    }

    return 0;
}