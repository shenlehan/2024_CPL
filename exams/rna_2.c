#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 105
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct node {
    char ch;
    struct node *next;
} Node;

typedef struct LinkList {
    Node *head, *tail;
} LinkList;

LinkList *LL;

int n, m;
char *orgi[N], *repl[N], rna[10005];

void print(LinkList *ll) {
    for (Node *p = ll->head; p; p = p->next) {
        printf("%c", p->ch);
    }
    puts("");
}

LinkList *build(const char *str) {
    LinkList *res = calloc(1, sizeof(LinkList));
    Node *newNode;
    for (const char *p = str; *p; ++p) {
        if (res->head == NULL) {
            res->head = calloc(1, sizeof(Node));
            res->head->ch = *p;
            res->tail = res->head;
        } else {
            newNode = calloc(1, sizeof(Node));
            newNode->ch = *p;
            res->tail->next = newNode;
            res->tail = newNode;
        }
    }
    return res;
}

int match(Node *p, int id) {
    int len = strlen(orgi[id]), i;
    for (i = 0; p != NULL && i < len; ++i, p = p->next) {
        if (p->ch != orgi[id][i]) return 0;
    }
    if (i != len) return 0;
    else return 1;
}

void Free(Node *st, Node *end) {
    Node *tmp;
    while (st != end) {
        tmp = st->next;
        free(st);
        st = tmp;
    }
    free(end);
}

void replace(int id) {
    int len = strlen(orgi[id]);
    LinkList *temp;
    for (Node *p = LL->head, *prev = NULL; p; prev = p, p = p->next) {
        // print(LL);
        if (match(p, id)) {
            temp = build(repl[id]);
            Node *end = temp->head;
            for (int i = 0; i < len - 1; ++i) {
                end = end->next;
            }
            temp->tail->next = end->next;
            if (prev == NULL) {
                LL->head = temp->head;
            } else {
                prev->next = temp->head;
            }
            Free(p, end);
            p = temp->tail;
        }
    }
}

int main() {
    freopen("rna.txt", "r", stdin);
    scanf("%s %d %d", rna, &n, &m);
    for (int i = 0; i < n; ++i) {
        orgi[i] = malloc(sizeof(char) * 105);
        repl[i] = malloc(sizeof(char) * 105);
        scanf("%s %s", orgi[i], repl[i]);
    }
    LL = build(rna);
    while (m--) {
        for (int i = 0; i < n; ++i) {
            replace(i);
        }
    }
    print(LL);
    return 0;
}