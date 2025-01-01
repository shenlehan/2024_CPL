#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 5005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    int l, r;
    struct Node *next;
} Node;

typedef struct Opt {
    int l, r;
    int suc;
} Opt;

Node *head, *tail;
Opt a[N];
int n, T, opt, size, id, allocNum;

void print() {
    int suc = 0;
    for (Node *p = head; p; p = p->next) {
        if (p->l < p->r) {
            suc = 1;
            printf("[%d,%d) ", p->l, p->r);
        }
    }
    if (!suc) printf("NULL");
    puts("");
}

void init() {
    head = calloc(1, sizeof(Node));
    head->l = 0, head->r = n;
    tail = head;
}

void merge() {
    for (Node *p = head; p; p = p->next) {
        while (p->next && (p->r == p->next->l)) {
            p->r = p->next->r;
            p->next = p->next->next;
        }
    }
}

int alloc(int sz) {
    for (Node *p = head; p; p = p->next) {
        if ((p->r - p->l) >= sz) {
            a[allocNum].l = p->l;
            a[allocNum].r = p->l + sz;
            a[allocNum].suc = 1;
            p->l += sz;
            merge();
            // log("l=%d r=%d", p->l, p->r);
            // log("a[%d].l=%d, a[%d].r=%d", allocNum, a[allocNum].l, allocNum, a[allocNum].r);
            return 1;
        }
    }
    return 0;
}

void Free(int id) {
    int l = a[id].l, r = a[id].r;
    Node *new = calloc(1, sizeof(Node));
    new->l = l, new->r = r;
    // log("______________");
    // print();
    // before head
    if (new->r <= head->l) {
        new->next = head;
        head = new;

    } else {

        // after p
        int suc = 0;
        for (Node *p = head; p->next; p = p->next) {
            if (p->r <= new->l && new->r <= p->next->l) {
                suc = 1;
                new->next = p->next;
                p->next = new;
                break;
            }
        }

        // insert after tail
        if (suc == 0) {
            tail->next = new;
            tail = new;
        }
    }
    // print();
    merge();
    // print();
}

int main() {
    freopen("mem.txt", "r", stdin);
    scanf("%d %d", &T, &n);
    init();
    while (T--) {
        scanf("%d", &opt);
        if (opt == 1) {
            scanf("%d", &size);
            ++allocNum;
            // alloc size
            if(alloc(size)) {
                printf("%d\n", a[allocNum].l);
            } else {
                puts("malloc fail");
            }

        } else if (opt == 2) {
            scanf("%d", &id);
            if (id <= 0 || id > allocNum) {
                puts("free fail");
            } else if (a[id].suc == 0) {
                puts("free fail");
            } else {
                Free(id);
                a[id].suc = 0;
                puts("free success");
            }


        } else {
            print();

        }
    }
    return 0;
}