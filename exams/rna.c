#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 10005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct node {
    char ch;
    struct node *next;
} Node;

Node *head, *tail;

int n, m;
char *rna;
char *orig[105], *repl[105];

void print() {
    for (Node *p = head; p; p = p->next) {
        printf("%c->", p->ch);
    }
    puts("NULL");
}

Node *curHead, *newNode, *curTail;
Node *build(const char *str) {
    int len = strlen(str);
    // log("len=%d",len);
    curHead = NULL;
    for (int i = 0; i < len; ++i) {
        // log("i=%d", i);
        if (curHead == NULL) {
            // log("SUCCESS!");
            curHead = calloc(1, sizeof(Node));
            curHead->ch = str[i];
            curTail = curHead;
        } else {
            // log("SUCCESS!");
            newNode = calloc(1, sizeof(Node));
            newNode->ch = str[i];
            curTail->next = newNode;
            curTail = newNode;
        }
        
    }
    return curHead;
}

Node *find(Node *start, int id) {
    if (start == NULL) return NULL;

    Node *p = start;
    int len = strlen(orig[id]);
    for (; p; p = p->next) {
        int suc = 0, tot = 0;
        for (Node *cur = p; cur != NULL && tot < len; cur = cur->next) {
            if (cur->ch == orig[id][tot]) {
                ++tot;
            } else {
                break;
            }
        }

        if (tot == len) {
            return p;
        }
    }
    return NULL;
}

void replace(Node *start, int id) {
    Node *tempHead = build(repl[id]);
    Node *tempTail;
    Node *end = start; // end of string to be replaced
    Node *prev; // prev of the string to be replace
    Node *temp;
    int len = strlen(orig[id]);
    for (int i = 0; i < len - 1; ++i, end = temp) {
        temp = end->next;
        free(end);
    }
    for (tempTail = tempHead; tempTail->next; tempTail = tempTail->next);

    tempTail->next = end->next;
    end->next = NULL;

    if (tail == end) {
        tail = tempTail;
    }

    if (start != head) {
        for (prev = head; prev->next != start; prev = prev->next);
        prev->next = tempHead;
    } else {
        head = tempHead;
    }

    // log("start=%p end=%p", start,end);
    // log("start->next=%p", start->next);

    // Node *p, *temp;
    // log("FREE:");
    // Node *p = start, *temp;
    // while (p != end) {
    //     Node *temp = p;
    //     p = p->next;
    //     free(temp);
    // }
    // if (p) free(p);

    // print();
}

int main() {
    freopen("rna.txt", "r", stdin);
    rna = malloc(N * sizeof(char));
    scanf("%s %d %d", rna, &n, &m);
    for (int i = 1; i <= n; ++i) {
        orig[i] = malloc(sizeof(char) * 105);
        repl[i] = malloc(sizeof(char) * 105);
        scanf("%s %s", orig[i], repl[i]);
    }
    head = build(rna);
    tail = head;
    while (m--) {
        for (int i = 1; i <= n; ++i) {
            Node *pos = find(head, i);
            if (pos != NULL) {
                replace(pos, i);
                pos = find(pos->next, i);
            } else {
                break;
            }
        }
    }
    print();
    for (int i = 1; i <= n; ++i) {
        free(orig[i]);
        free(repl[i]);
        // scanf("%s %s", orig[i], repl[i]);
    }
    free(rna);
    return 0;
}