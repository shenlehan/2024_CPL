#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define B 2005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    // 0 -> B - 1
    char str[B + 5];
    int size;
    struct Node *next;
} Node;

Node *head, *tail;
char comd[5], str[100005];
int n, q, x;

void print() {
    for (Node *p = head; p; p = p->next) {
        for (int i = 0; i < p->size; ++i) {
            printf("%c", p->str[i]);
        }
        printf("(%d)->", p->size);
    }
    puts("NULL");
}

Node *init() {
    Node *curHead = calloc(1, sizeof(Node));
    Node *cur = curHead, *newNode;
    n = strlen(str);
    for (int i = 0; i < n; ++i) {
        if (cur->size < B) {
            cur->str[(cur->size)++] = str[i];
        } else {
            newNode = calloc(1, sizeof(Node));
            cur->next = newNode;
            cur = newNode;
            cur->str[(cur->size)++] = str[i];
        }
    }
    return curHead;
}

Node *get(int pos) {
    for (Node *p = head; p; p = p->next) {
        if (0 <= pos && pos < p->size) {
            return p;
        }
        pos -= p->size;
    }
    return NULL;
}

int count(int pos) {
    for (Node *p = head; p; p = p->next) {
        if (0 <= pos && pos < p->size) {
            return pos;
        }
        pos -= p->size;
    }    
}

void query(int pos) {
    for (Node *p = head; p; p = p->next) {
        if (0 <= pos && pos < p->size) {
            // log("");
            printf("%c\n", p->str[pos]);
            return;
        }
        pos -= p->size;
    }
}

void split(Node *cur, int pos) {
    // log("pos=%d", pos);
    Node *newNode = calloc(1, sizeof(Node));
    newNode->next = cur->next;
    cur->next = newNode;

    for (int i = pos; i < cur->size; ++i) {
        newNode->str[(newNode->size)++] = cur->str[i];
    }
    cur->size = pos;
    // print();
}

void merge() {
    Node *temp;
    for (Node *p = head; p; p = p->next) {
        while (p->next && (p->size + p->next->size) <= B) {
            for (int i = 0; i < p->next->size; ++i) {
                p->str[(p->size)++] = p->next->str[i];
            }
            temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
    }
}

void insert(Node *cur) {
    Node *newNode = init(), *temp = newNode;
    for (; temp->next; temp = temp->next);
    temp->next = cur->next;
    cur->next = newNode;
}

void ins(int pos) {
    if (pos == -1) {
        Node *newHead = init();
        Node *temp = newHead;
        for (; temp->next; temp = temp->next);
        temp->next = head;
        head = newHead;
        return;
    }
    Node *cur = get(pos);
    // copy splitPos->end
    int splitPos = count(pos);
    // log("splitPos=%d", splitPos); 
    split(cur, splitPos);
    // insert after cur
    // print();
    insert(cur);
    // print();
    merge();
    // print();
}

int main() {
    freopen("ull.txt", "r", stdin);
    scanf("%d %d", &n, &q);
    scanf("%s", str);
    head = init();
    print();
    while (q--) {
        // log("q=%d", q);
        scanf("%s %d", comd, &x);
        if (comd[0] == 'Q') {
            --x;
            // log("x=%d", x);
            query(x);
        } else {
            scanf("%s", str);
            ins(x);
        }
    }
    return 0;
}