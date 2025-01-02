#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define B 2005

typedef struct Node {
    char str[B];
    int size;
    struct Node *next;
} Node;

typedef struct Linklist {
    Node *head, *tail;
} LL;

LL *list;
Node *newNode;
int n, q, x;
char str[1000005], cmd[5];

LL *build(const char *str) {
    LL *res = calloc(1, sizeof(LL));
    for (const char *p = str; *p; ++p) {
        if (res->head == NULL) {
            res->head = calloc(1, sizeof(Node));
            res->head->str[(res->head->size)++] = *p;
            res->tail = res->head;
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
    for (Node *p = list->head; p; p = p->next) {
        if (0 <= pos && pos < p->size) {
            printf("%c\n", p->str[pos]);
            return;
        }
        pos -= p->size;
    }
}

void merge() {
    for (Node *p = list->head; p; p = p->next) {
        while (p->next && p->size + p->next->size <= B) {
            for (int i = 0; i < p->next->size; ++i) {
                p->str[(p->size)++] = p->next->str[i];
            }
            p->next = p->next->next;
        }
    }
}

void insert(const char *str, int pos) {
    LL *temp = build(str);
    if (pos == -1) { // insert before head
        temp->tail->next = list->head;
        list->head = temp->head;
        merge();
        return;
    }

    Node *cur;
    for (cur = list->head; cur; cur = cur->next) {
        if (0 <= pos && pos < cur->size) break;
        pos -= cur->size;
    }
    newNode = calloc(1, sizeof(Node));
    for (int i = pos + 1; i < cur->size; ++i) {
        newNode->str[(newNode->size)++] = cur->str[i];
    }
    cur->size = pos + 1;
    newNode->next = cur->next;
    cur->next = temp->head;
    temp->tail->next = newNode;
    merge();
}

int main() {
    scanf("%d %d %s", &n, &q, str);
    list = build(str);
    while (q--) {
        scanf("%s %d", cmd, &x);
        --x;
        if (cmd[0] == 'Q') {
            query(x);
        } else {
            scanf("%s", str);
            insert(str, x);
        }
    }
    return 0;
}