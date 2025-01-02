#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define N 10005

typedef struct Node {
    char ch;
    struct Node *next;
} Node;

typedef struct Linklist {
    Node *head, *tail;
} LL;

LL *ll, *temp;
Node *newNode, *toFree;
int n, m;
char rna[N];
char orgi[105][105], repl[105][105];

void print(LL *list) {
    for (Node *p = list->head; p; p = p->next) printf("%c", p->ch);
    puts("");
}

LL *build(const char *str) {
    LL *res = calloc(1, sizeof(LL));
    for (const char *p = str; *p; ++p) {
        if (res->head == NULL) {
            res->head = calloc(1, sizeof(Node));
            res->tail = res->head;
            res->head->ch = *p;
        } else {
            newNode = calloc(1, sizeof(Node));
            newNode->ch = *p;
            res->tail->next = newNode;
            res->tail = newNode;
        }
    }
    return res;
}

Node *match(Node *p, int id) {
    int len = strlen(orgi[id]);
    Node *cur;
    int i = 0;
    for (cur = p; cur && i < len - 1; ++i, cur = cur->next)
        if (cur->ch != orgi[id][i]) return NULL;
    if (!cur) return NULL;
    if (cur->ch != orgi[id][len - 1]) return NULL;
    else return cur;
}

void Free(Node *start, Node *end) {
    if (!start) return;
    for (toFree = start; toFree != end; toFree = newNode) {
        newNode = toFree->next;
        free(toFree);
    }
    free(end);
}

void replace(int id) {
    Node *prev = NULL, *pos = NULL, *end = NULL;
    for (Node *cur = ll->head; cur; ) {
        for (pos = cur; pos; prev = pos, pos = pos->next) {
            end = match(pos, id);
            if (end) break;
        }
        if (!end) return;
        temp = build(repl[id]);
        if (prev == NULL) {
            temp->tail->next = end->next;
            ll->head = temp->head;
            return;
        }
        prev->next = temp->head;
        temp->tail->next = end->next;
        cur = end->next;
        Free(pos, end);
    }
}

int main() {
    scanf("%s %d %d", rna, &n, &m);
    ll = build(rna);
    for (int i = 0; i < n; ++i) {
        scanf("%s %s", orgi[i], repl[i]);
    }
    while (m--) 
        for (int i = 0; i < n; ++i) 
            replace(i);
    print(ll);
    return 0;
}