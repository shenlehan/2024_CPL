#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 5005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    // [l, r)
    int l, r;
    struct Node *next, *prev;
} Node;

typedef struct work {
    int l, r;
    int suc;
} work;

work a[N];
Node *head, *tail;
int T, n, alloNum, opt;

void print() {
    int suc = 0;
    for (Node *p = head; p; p = p->next) {
        if (p->l == p->r) continue;
        printf("[%d,%d) ", p->l, p->r);
        suc = 1;
    }
    // puts("NULL");
    if (!suc) printf("NULL");
    puts("");
}

void init() {
    head = calloc(1, sizeof(Node));
    head->l = 0, head->r = n;
    tail = head;
}

int alloc(int size) {
    for (Node *p = head; p; p = p->next) {
        if ((p->r - p->l) >= size) {
            // record the allocation
            a[alloNum].l = p->l;
            a[alloNum].r = p->l + size;
            a[alloNum].suc = 1;
            printf("%d\n", p->l);
            p->l += size;
            // log("");
            return 1;
        }
    }
    return 0;
}

void merge() {
    for (Node *p = head; p; p = p->next) {
        while (p->next && p->next->l == p->r) {
            if (p->next == tail) tail = p;
            p->r = p->next->r;
            p->next = p->next->next;
            // if (!p->next) break;
        }
    }
}

void Free(int id) {
    int l = a[id].l, r = a[id].r;
    // before head
    Node *newNode = calloc(1, sizeof(Node));
    newNode->l = l, newNode->r = r;
    if (r <= head->l) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    // after p
    for (Node *p = head; p; p = p->next) {
        if (!p->next) {
            // insert at tail
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            merge();
            return;
        }
        if (p->r <= l && r <= p->next->l) {
            // insert after p
            newNode->next = p->next;
            p->next->prev = newNode;
            p->next = newNode;
            newNode->prev = p;
            merge();
            return;
        }
    }    
}

int main() {
    freopen("mem.txt", "r", stdin);
    scanf("%d %d", &T, &n);
    init();
    for (int NUM = 1; NUM <= T; ++NUM) {
        scanf("%d", &opt);
        if (opt == 1) {
            int size;
            scanf("%d", &size);
            // allocate size
            ++alloNum;
            if(!alloc(size)) {
                puts("malloc fail");
            }
            // print();
        } else if (opt == 2) {
            int id;
            scanf("%d", &id);
            if (a[id].suc != 0) {
                Free(id);
                a[id].suc = 0;
                printf("free success\n");
            } else {
                printf("free fail\n");
            }
        } else {
            print();
        }
    }
    return 0;
}