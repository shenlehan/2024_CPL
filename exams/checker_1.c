#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 100005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int T, len, modelLen, vis[105];
char ans[N], std[N], model[N];

void init() {
    len = modelLen = 0;
    memset(vis, 0, sizeof(vis));
    memset(model, 0, sizeof(model));
}

int check_par() {
    for (int i = 0, j = modelLen - 1; i < j; i++, j--) {
        if (ans[i] != ans[j]) return 0;
    }
    return 1;
}

void getstd() {
    for (int i = 0; i < len; ++i) {
        if (std[i] == '?' && std[len - i - 1] != '?') std[i] = std[len - i - 1];
    }
    for (int i = 0; i < len; ++i) {
        if (std[i] != '?') {
            model[modelLen++] = std[i];
        } else {
            model[modelLen++] = '*';
            model[modelLen++] = '*';
        }
    }
    model[modelLen] = 0;
}

int calc() {
    int lenAns = strlen(ans);
    if (!check_par()) return 0;
    if (modelLen != lenAns) return 0;
    char x = 0, y = 0;
    for (int i = 0; i < modelLen; i++) {
        if (model[i] == '*') {
            if (x == 0)
                x = ans[i];
            else {
                y = ans[i];
                if ((!isdigit(x)) || (!isdigit(y))) return 0;
                if (x == y) {
                    int t = (x - '0') * 10 + (y - '0');
                    if (vis[t] == 2) return 0;
                    vis[t]++;
                } else {
                    int t1 = (x - '0') * 10 + (y - '0');
                    int t2 = (y - '0') * 10 + (x - '0');
                    if (vis[t1] == 2 && vis[t2] == 2) return 0;
                    if (vis[t1] < 2)
                        vis[t1]++;
                    else {
                        vis[t2]++;
                    }
                }
                x = y = 0;
            }
        } else {
            if (ans[i] != model[i]) return 0;
        }
    }
    return 1;
}

int main() {
    freopen("checker.txt", "r", stdin);
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%d %s %s", &len, std, ans);
        getstd();
        // log("model=%s",model);
        if(!calc()) {
            puts("Wrong Answer!");
        } else {
            puts("Correct.");
        }
    }
    return 0;
}