#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 2505
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    int val;
    struct Node *d, *r;
} Node;

Node map[N][N];
int n, m, q;
int x1, y1, x2, y2, x3, y3, x4, y4, a;

void swap(Node **p1, Node **p2) {
    Node *tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void printRow(int i) {
    for (Node *p = &map[i][0]; p; p = p->r) {
        printf("%d ", p->val);
    }
    puts("");
}

Node *get(int i, int j) {
    Node *p = &map[i][0];
    for (int k = 0; k < j; ++k) {
        // log("p->val=%d",p->val);
        p = p->r;
    }
    return p;
}

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            map[i][j].d = &map[i + 1][j];
            map[i][j].r = &map[i][j + 1];
            map[i][j].val = i * m + j;
        } 
    }
}

int main() {
    // freopen("lineup.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &q);
    init();
    
    while (q--) {
        scanf("%d %d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &a);
        // printf("%d %d %d %d %d %d %d %d %d\n", x1, y1, x2, y2, x3, y3, x4, y4, a);

        Node *p1 = get(x1, y1 - 1), *p2 = get(x3, y3 - 1),
        *p3 = get(x1 - 1, y1), *p4 = get(x3 - 1, y3),
        *p5 = get(x2, y1), *p6 = get(x4, y3),
        *p7 = get(x1, y2), *p8 = get(x3, y4);

        for (int i = 0; i < abs(x2 - x1) + 1; ++i) {
            Node *temp = p1->r;
            p1->r = p2->r;
            p2->r = temp;
            p1 = p1->d, p2 = p2->d;
        }
// here
        for (int i = 0; i < abs(y2 - y1) + 1; ++i) {
            Node *temp = p3->d;
            p3->d = p4->d;
            p4->d = temp;
            p3 = p3->r, p4 = p4->r;
        }

        for (int i = 0; i < abs(y1 - y2) + 1; ++i) {
            Node *temp = p5->d;
            p5->d = p6->d;
            p6->d = temp;
            p5 = p5->r, p6 = p6->r;
        }

        // printf("p1=%d,p2=%d\n",p1->val,p2->val);
        for (int i = 0; i < abs(x1 - x2) + 1; ++i) {
            Node *temp = p7->r;
            p7->r = p8->r;
            p8->r = temp;
            p7 = p7->d, p8 = p8->d;
        }

        long long ans = 0;
        Node *p = get(a, 0)->r;
        for (int i = 1; i <= m; ++i) {
            // log("p->val=%d", p->val);
            ans += p->val;
            p = p->r;
        }
        printf("%lld\n",ans);
    }

    return 0;
}