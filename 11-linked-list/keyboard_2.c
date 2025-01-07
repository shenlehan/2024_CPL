#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 1000005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); printf("\n"); } while(0)

typedef struct Node {
    char c;
    struct Node *prev, *next, *last_same;
} Node;

typedef struct LinkList {
    Node *head, *tail;
    Node *last_upper, *last_lower;
} LL;

LL *ll;
Node *newNode, *prev, *next, *toFree;
int q, k;
char str[N], output[N];

void print() {
    for (Node *p = ll->head; p; p = p->next) {
        printf("%c->", p->c);
    }
    puts("NULL");
}

void insert(const char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if (s[i] == 'm') {
            if (!ll->last_lower) continue;
            prev = ll->last_lower->prev,
            next = ll->last_lower->next;

            if (prev == NULL) ll->head = ll->head->next; // be aware of the head
            else prev->next = next;

            if (next == NULL) ll->tail = ll->tail->prev; // be aware of the tail
            else next->prev = prev;

            toFree = ll->last_lower;
            ll->last_lower = ll->last_lower->last_same;
            free(toFree);

        } else if (s[i] == 'M') {
            if (!ll->last_upper) continue;
            prev = ll->last_upper->prev,
            next = ll->last_upper->next;

            if (prev == NULL) ll->head = ll->head->next;
            else prev->next = next;

            if (next == NULL) ll->tail = ll->tail->prev;
            else next->prev = prev;

            toFree = ll->last_upper;
            ll->last_upper = ll->last_upper->last_same;
            free(toFree);           

        } else {
            if (ll->head == NULL) {
                // empty
                ll->head = calloc(1, sizeof(Node));
                ll->tail = ll->head;
                ll->head->c = s[i];
                if (isupper(s[i])) ll->last_upper = ll->head;
                else ll->last_lower = ll->head;
            } else {
                newNode = calloc(1, sizeof(Node));
                newNode->c = s[i];
                if (isupper(s[i])) {
                    newNode->last_same = ll->last_upper;
                    ll->last_upper = newNode;
                } else {
                    newNode->last_same = ll->last_lower;
                    ll->last_lower = newNode;
                }
                newNode->prev = ll->tail;
                ll->tail->next = newNode;
                ll->tail = newNode;
            }
        }
        // log("HERE, s[%d]=%c",i,s[i]);
        // print();
    }

}

void query(int pos) {
    int i = 0;
    for (Node *p = ll->tail; i < pos; ++i, p = p->prev) {
        output[i] = p->c;
        // log("i=%d",i);
    }
    for (--i; i >= 0; --i) {
        printf("%c", output[i]);
    }
    puts("");
}

int main() {
    freopen("keyboard.txt", "r", stdin);
    scanf("%d", &q);
    ll = calloc(1, sizeof(LL));
    while (q--) {
        scanf("%s", str);
        if (str[0] == '?') {
            scanf("%d", &k);
            // log("k=%d",k);
            query(k);
        } else {
            insert(str);
        }
    }
    return 0;
}