#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define N 5005

typedef struct Node {
    /**
     * [l, r)
     * size = r - l;
     */
    int l, r;
    struct Node *next;
} Node;

typedef struct Linklist {
    Node *head, *tail;
} LL;

typedef struct Alloc {
    int l, r, suc;
} Alloc;

LL *ll;
Node *toFree, *newNode;
Alloc a[N];
int T, n, opt, id, size, allocNum;

void init() {
    ll = calloc(1, sizeof(LL));
    ll->head = calloc(1, sizeof(Node));
    ll->tail = ll->head;
    ll->head->l = 0, ll->head->r = n;
}

void merge() {
    for (Node *p = ll->head; p; p = p->next) {
        while (p->next && p->r == p->next->l) {
            toFree = p->next;
            p->r = p->next->r;
            p->next = p->next->next;
            free(toFree);
        }
    }
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

void alloc(int size) {
    ++allocNum;
    for (Node *p = ll->head; p; p = p->next) {
        if ((p->r - p->l) >= size) {
            printf("%d\n", p->l);
            a[allocNum].l = p->l;
            a[allocNum].r = p->l + size;
            a[allocNum].suc = 1;
            p->l += size;
            merge();
            return;
        }
    }

    puts("malloc fail");
    a[allocNum].suc = 0;
}

void Free(int id) {
    newNode = calloc(1, sizeof(Node));
    newNode->l = a[id].l, newNode->r = a[id].r;
    a[id].suc = 0;

    // insert before head
    if (newNode->r <= ll->head->l) {
        newNode->next = ll->head;
        ll->head = newNode;
        merge();
        return;
    }

    // insert after head 
    int ok = 0;
    for (Node *p = ll->head; p->next; p = p->next) {
        if (p->r <= newNode->l && newNode->r <= p->next->l) {
            newNode->next = p->next;
            p->next = newNode;
            ok = 1;
            break;
        }
    }
    if (!ok) {
        ll->tail->next = newNode;
        ll->tail = newNode;
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
            alloc(size);
        } else if (opt == 2) {
            scanf("%d", &id);
            if (id <= 0 || id > allocNum) {
                puts("free fail");
            }
            if (a[id].suc == 0) {
                puts("free fail");
            } else {
                Free(id);
                puts("free success");
            }
        } else {
            print();
        }
    }
    return 0;
}