#include <stdio.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int T, len, len_ans;
char str[100005], ans[100005];
int used[105];

int main() {
    scanf("%d", &T);
    
    while (T--) {
        memset(used, 0, sizeof(used));
        scanf("%d %s %s", &len, str, ans);
        int ok = 1;
        len_ans = strlen(ans);
        for (int i = 0; i < len_ans / 2; ++i) {
            if (ans[i] != ans[len_ans - i - 1]) {
                ok = 0;
                // log("");
                puts("Wrong Answer!");
                break;
            }
        }
        if (!ok) continue;

        for (int pstr = 0, pans = 0; pans < len_ans; ++pans, ++pstr) {
            if (str[pstr] == '?' && str[len - pstr - 1] == '?') {
                ++pans;
                continue;
            }
            if (str[pstr] == '?') {
                continue;
            }
            if (str[pstr] != ans[pans]) {
                ok = 0;
                // log("");
                puts("Wrong Answer!");
                break;
            }
        }
        if (!ok) continue;

        for (int pstr = 0, pans = 0; pans < len_ans / 2; ++pans, ++pstr) {
            if (str[pstr] == '?' && str[len - pstr - 1] == '?') {
                int x = ans[pans] - '0';
                x = x * 10 + ans[pans + 1] - '0';
                int y = ans[pans + 1] - '0';
                y = y * 10 + ans[pans] - '0';
                if (!used[x]) {
                    used[x] = 1;
                } else if (!used[y]) {
                    used[y] = 1;
                } else {
                    ok = 0;
                    // log("");
                    puts("Wrong Answer!");
                    break;                    
                }
                ++pans;
            }
        }
        if (!ok) continue;
        puts("Correct.");
    }
    
    return 0;
}