#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define B 3
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); } while (0) 

typedef struct Node {
    char str[B];
    int size;
    struct Node *next;
} Node;

typedef struct LinkList {
    Node *head, *tail;
} LL;

LL *ll;
int n, m, q, pos;
char str[100005], comd[5];

void print(LL *list) {
    for (Node *p = list->head; p; p = p->next) {
        for (int i = 0; i < p->size; ++i) {
            printf("%c", p->str[i]);
        }
        printf("->");
    }
    puts("NULL");
}

LL *build(char *s) {
    LL *ret = calloc(1, sizeof(LL));
    Node *newNode = NULL;
    for (char *p = s; *p; ++p) {
        if (ret->head == NULL) {
            ret->head = calloc(1, sizeof(Node));
            ret->head->str[(ret->head->size)++] = *p;
            ret->tail = ret->head;
        } else if (ret->tail->size < B) {
            ret->tail->str[(ret->tail->size)++] = *p;
        } else {
            newNode = calloc(1, sizeof(Node));
            newNode->str[(newNode->size)++] = *p;
            ret->tail->next = newNode;
            ret->tail = newNode;
        }
    }
    // print(ret);
    return ret;
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
        while (p->next && p->size + p->next->size <= B) {
            for (int i = 0; i < p->next->size; ++i) {
                p->str[(p->size)++] = p->next->str[i];
            }
            p->next = p->next->next;
        }
    }
}

void insert(char *s, int pos) {
    Node *cur = NULL;
    for (cur = ll->head; cur; cur = cur->next) {
        if (0 <= pos && pos < cur->size) {
            break;
        }
        pos -= cur->size;
    }
    Node *newNode = calloc(1, sizeof(Node));
    for (int i = pos + 1; i < cur->size; ++i) {
        newNode->str[(newNode->size)++] = cur->str[i];
    }
    cur->size = pos + 1;
    LL *temp = build(s);
    temp->tail->next = newNode;
    newNode->next = cur->next;
    cur->next = temp->head;
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