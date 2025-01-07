#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    int l, r;
    struct Node *next;
} Node;

typedef struct LinkList {
    Node *head, *tail;
} LL;

typedef struct Alloc {
    int l, r;
    int suc;
} Alloc;

LL *ll;
Alloc a[N];
int T, n, opt, size, id;
int allocNum;

void init() {
    ll = calloc(1, sizeof(LL));
    ll->head = calloc(1, sizeof(Node));
    ll->head->l = 0, ll->head->r = n;
}

void merge() {
    Node *toFree;
    for (Node *p = ll->head; p; p = p->next) {
        while (p->next && p->r == p->next->l) {
            p->r = p->next->r;
            toFree = p->next;
            p->next = p->next->next;
            free(toFree);
        }
    }
}

void alloc(int sz) {
    for (Node *p = ll->head; p; p = p->next) {
        if ((p->r - p->l) >= sz) {
            printf("%d\n", p->l);
            a[allocNum].l = p->l;
            a[allocNum].r = p->l + sz;
            a[allocNum].suc = 1;
            p->l += sz;
            merge();
            return;
        }
    }
    puts("malloc fail");
}

void print() {
    int suc = 0;
    for (Node *p = ll->head; p; p = p->next) {
        if (p->l == p->r) continue;
        suc = 1;
        printf("[%d,%d) ", p->l, p->r);
    }
    if (!suc) printf("NULL");
    puts("");
}

void Free(int id) {
    Node *newNode = calloc(1, sizeof(Node));
    newNode->l = a[id].l, newNode->r = a[id].r;
    a[id].suc = 0;
    Node *prev;
    if (newNode->r <= ll->head->l) {
        newNode->next = ll->head;
        ll->head = newNode;
    } else {
        int suc = 0;
        for (prev = ll->head; prev->next; prev = prev->next) {
            if (prev->r <= newNode->l && newNode->r <= prev->next->l) {
                suc = 1;
                newNode->next = prev->next;
                prev->next = newNode;
            }
        }
        if (!suc) {
            ll->tail->next = newNode;
            ll->tail = newNode;
        }
    }

    merge();
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
            alloc(size);
        } else if (opt == 2) {
            scanf("%d", &id);
            if (id <= 0 || id > allocNum) {
                puts("free failure");
            } else if (a[id].suc == 0) {
                puts("free failure");
            } else {
                puts("free success");
                Free(id);
            }

        } else {
            print();
        }
    }
    return 0;
}