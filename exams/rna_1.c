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
char orgi[N][N], repl[N][N], rna[10005];

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

void find(LinkList *ll, int id) {
    if (ll == NULL || ll->head == NULL) {
        return;
    }
    int cnt = 0, len = strlen(orgi[id]);
    LinkList *pos = calloc(1, sizeof(LinkList));
    Node *p;
    for (p = ll->head; p; ) {
        pos->head = p;
        cnt = 0;
        for (pos->tail = pos->head; pos->tail && cnt < len - 1; ++cnt) {
            if (pos->tail->ch != orgi[id][cnt]) {
                break;
            }
            pos->tail = pos->tail->next;
        }
        if (pos->tail == NULL || pos->tail->ch != orgi[id][cnt]) {
            p = p->next;
            continue;
        }
        ++cnt;
        if (cnt == len) { // found
            // p is start
            LinkList *temp = build(repl[id]);
            // find prev of p
            if (pos->head == ll->head) {
                temp->tail->next = pos->tail->next;
                ll->head = temp->head;
            } else {
                Node *prev;
                for (prev = ll->head; prev->next != pos->head; prev = prev->next);
                prev->next = temp->head;
                temp->tail->next = pos->tail->next;
                // print(temp);
            }
            p = temp->tail;
        }
    }
}

int main() {
    freopen("rna.txt", "r", stdin);
    scanf("%s %d %d", rna, &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s %s", orgi[i], repl[i]);
    }
    LL = build(rna);
    while (m--) {
        for (int i = 0; i < n; ++i) {
            find(LL, i);
        }
    }
    print(LL);
    return 0;
}