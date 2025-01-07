#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define B 3

typedef struct Node {
    char str[B];
    int size;
    struct Node *next;
} Node;

typedef struct LinkList {
    Node *head, *tail;
} LL;

LL *ll;
Node *newNode;
int n, q;
int pos;
char str[1000005], comd[5];

void print(LL *list) {
    for (Node *p = list->head; p; p = p->next) {
        for (int i = 0; i < p->size; ++i)
            printf("%c", p->str[i]);
        printf("->");
    }
    puts("NULL");
}

LL *build(const char *s) {
    LL *res = calloc(1, sizeof(LL));
    for (const char *p = s; *p; ++p) {
        if (res->head == NULL) {
            res->head = calloc(1, sizeof(Node));
            res->tail = res->head;
            res->head->str[(res->head->size)++] = *p;
        } else {
            if (res->tail->size < B) {
                res->tail->str[(res->tail->size)++] = *p;
            } else {
                newNode = calloc(1, sizeof(Node));
                newNode->str[(newNode->size)++] = *p;
                res->tail->next = newNode;
                res->tail = newNode;
            }
        }
    }   
    return res;
}

void query(int pos) {
    for (Node *p = ll->head; p; p = p->next) {
        if (0 <= pos && pos < p->size) {
            printf("%c\n", p->str[pos]);
        }
        pos -= p->size;
    }
}

void merge() {
    for (Node *p = ll->head; p; p = p->next) {
        while (p->next && p->next->size + p->size <= B) {
            for (int i = 0; i < p->next->size; ++i) {
                p->str[(p->size)++] = p->next->str[i];
            }
            p->next = p->next->next;
        }
    }
}

void printNode(Node *node) {
    for (int i = 0; i < node->size; ++i) {
        printf("%c",node->str[i]);
    }
    puts("->");
}

void insert(const char *s, int pos) {
    if (pos == -1) {
        LL *temp = build(s);
        temp->tail->next = ll->head;
        ll->head = temp->head;
        merge();
        return;
    }
    
    Node *cur;
    for (cur = ll->head; cur; cur = cur->next) {
        if (0 <= pos && pos < cur->size) break;
        pos -= cur->size;
    }

    // log("cur->str[pos]=%c pos=%d", cur->str[pos], pos);
    LL *temp = build(s);
    newNode = calloc(1, sizeof(Node));
    for (int i = pos + 1; i < cur->size; ++i) {
        newNode->str[(newNode->size)++] = cur->str[i];
    }
    cur->size = pos + 1;

    // print(res);
    newNode->next = cur->next;
    cur->next = temp->head;
    temp->tail->next = newNode;
    // print(ll);
    merge();
    // print(ll);
}

int main() {
    freopen("ull.txt", "r", stdin);
    scanf("%d %d %s", &n, &q, str);
    ll = build(str);
    print(ll);
    while (q--) {
        scanf("%s %d", comd, &pos);
        --pos;
        if (comd[0] == 'Q') {
            query(pos);
        } else {
            scanf("%s", str);
            insert(str, pos);
        }
    }
    return 0;
}