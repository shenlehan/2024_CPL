#include <stdio.h>

int ans[20] = {
    0, 
    0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 1
};

int ans1 = -1, ans2 = 0, ans3 = 0, n;

int main() {
    scanf("%d", &n);
    int i;

    while (n--) {
        scanf("%d", &i);
        ans1 &= i * ans[i];
        ans2 |= i * ans[i];
        ans3 ^= i * ans[i];
    }

    printf("%d %d %d", ans1, ans2, ans3);

    return 0;
}