#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int n, q, tot = 1;

struct mem {
    int size, id;
    struct mem *nxt;
} *head;

void add(int id, int sz) {
    for (struct mem *p = head; p != NULL; p = p->nxt) {
        if (!p->id && p->size == sz) {
            p->id = id;
            return;
        }
    }

    struct mem *new;
    while (1) {
        for (struct mem *p = head; p != NULL; p = p->nxt) {
            if (p->size > sz && !p->id) {
                new = calloc(1, sizeof(struct mem));
                ++tot;
                new->nxt = p->nxt;
                p->nxt = new;
                new->size = p->size - 1;
                --(p->size);
                break;
            } else if (p->size == sz && !p->id) {
                p->id = id;
                return;
            }
        }
    }
}

void print() {
    printf("%d\n", tot);
    for (struct mem *p = head; p != NULL; p = p->nxt) {
        printf("%d ", p->id);
    }
    puts("");
}

int main() {
    scanf("%d %d", &n, &q);
    head = calloc(1, sizeof(struct mem));
    head->size = n;
    
    while (q--) {
        char op[5];
        scanf("%s", op);
        if (op[0] == 'A') {
            int id, size;
            scanf("%d %d", &id, &size);
            int k = 0;
            while ((1 << k) < size) ++k;
            add(id, k);
        } else {
            print();
        }
    }

    return 0;
}