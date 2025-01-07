#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 2505
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    int val;
    struct Node *r, *d;
} Node;

Node map[N][N];
int n, m, q;
int x1, y1, x2, y2, x3, y3, x4, y4, a;
long long ans = 0;

void print() {
    for (int i = 1; i <= n; ++i) {
        for (Node *p = map[i][0].r; p->r; p = p->r) {
            printf("%d ", p->val);
        }
        puts("");
    }
}

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            map[i][j].val = i * m + j;
            map[i][j].r = &map[i][j + 1];
            map[i][j].d = &map[i + 1][j];
        }
    }
}

void swap(Node **a, Node **b) {
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

Node *get(int x, int y) {
    Node *res = &map[x][0];
    for (int i = 0; i < y; ++i) {
        res = res->r;
    }
    return res;
}

int main() {
    freopen("lineup.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &q);
    init();

    while (q--) {
        scanf("%d %d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &a);
        Node *p1 = get(x1, y1 - 1), *p2 = get(x3, y3 - 1);
        Node *p3 = get(x1 - 1, y1), *p4 = get(x3 - 1, y3);
        Node *p5 = get(x2, y1), *p6 = get(x4, y3);
        Node *p7 = get(x1, y2), *p8 = get(x3, y4);
        // log("%d %d", p1->val, p2->val);
        for (int i = 0; i < abs(x1 - x2) + 1; ++i) {
            swap(&(p1->r), &(p2->r));
            p1 = p1->d, p2 = p2->d;
        }

        for (int i = 0; i < abs(y1 - y2) + 1; ++i) {
            swap(&(p3->d), &(p4->d));
            p3 = p3->r, p4 = p4->r;
        }

        for (int i = 0; i < abs(y1 - y2) + 1; ++i) {
            swap(&(p5->d), &(p6->d));
            p5 = p5->r, p6 = p6->r;
        }

        for (int i = 0; i < abs(x1 - x2) + 1; ++i) {
            swap(&(p7->r), &(p8->r));
            p7 = p7->d, p8 = p8->d;
        }

        ans = 0;
        for (Node *p = map[a][0].r; p->r; p = p->r) {
            ans += p->val;
        }
        printf("%lld\n", ans);
    }

    return 0;
}