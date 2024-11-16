#include <stdio.h>
#include <stdlib.h>

int n, q;
char op[5];
int id, m, tot = 1;

struct mem {
    int size, nxt;
    int task_id;
} p[1000005];

void add(int sz, int id) {
    int same = 0;
    for (int i = 1; ~i; i = p[i].nxt) {
        if (p[i].size == sz && p[i].task_id == 0) {
            same = 1;
            p[i].task_id = id;
            break;
        }
    }
    if (same)
        return;
    
    int find = 0;
    while (1) {   
        for (int i = 1; ~i; i = p[i].nxt) {
            if (p[i].size > sz && p[i].task_id == 0) {
                p[i].size >>= 1;
                p[++tot].nxt = p[i].nxt;
                p[tot].size = p[i].size;
                p[i].nxt = tot;
                break;
            }
            if (p[i].size == sz && p[i].task_id == 0) {
                find = 1;
                p[i].task_id = id;
                break;
            } 
        }
        if (find) {
            break;
        }
    }
}

void print() {
    printf("%d\n", tot);
    for (int i = 1; ~i; i = p[i].nxt) {
        printf("%d ", p[i].task_id);
    }
    puts("");
}

int main() {
    scanf("%d %d", &n, &q);
    p[1].size = (1 << n);
    p[1].nxt = -1;
    while (q--) {
        scanf("%s", op);
        if (op[0] == 'A') {
            scanf("%d %d", &id, &m);
            int k = 0;
            while ((1 << k) < m) {
                ++k;
            }
            add((1 << k), id);
        } else if (op[0] == 'Q') {
            print();
        }
    }
    return 0;
}