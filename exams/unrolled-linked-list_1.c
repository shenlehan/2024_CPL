#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define B 5

typedef struct Node {
    char str[B];
    int size;
    struct Node *next;
} Node;

Node *head, *tail;
int n, q, x;
char str[1000005], cmd[5];

void Dump() {
    for (Node *p = head; p; p = p->next) {
        // log("p->size = %d", p->size);
        for (int i = 0; i < p->size; ++i) {
            printf("%c", p->str[i]);
        }
        printf("->");
    }
    puts("NULL");
}

// insert after pos
void Insert(Node *pos, Node* newNode) {
    newNode->next = pos->next;
    pos->next = newNode;
    if (pos == tail) {
        tail = newNode;
    }
}

void Append(char ch) {
    if (head == NULL) {
        head = calloc(1, sizeof(Node));
        head->str[0] = ch;
        head->size = 1;
        tail = head;
        return;
    }

    if (tail->size < B - 1) {
        tail->str[tail->size++] = ch;
        return;
    }

    Node *newNode = calloc(1, sizeof(Node));
    newNode->size = 1;
    newNode->str[0] = ch;
    Insert(tail, newNode);
}

void Query(int pos) {
    for (Node *p = head; p; p = p->next) {
        // log("p->size=%d, pos=%d", p->size, pos);
        if (0 <= pos && pos < p->size) {
            printf("%c\n", p->str[pos]);
            return;
        }
        pos -= p->size;
    }
    // Dump();
}

void merge(Node *n1, Node *n2) {
    if (n1->size + n2->size <= B - 1) {
        for (int i = 0; i < n2->size; ++i) {
            n1->str[n1->size++] = n2->str[i];
        }
        // log("n1->size=%d", n1->size);
        n1->next = n2->next;
    }
}

void InsertString(int pos, const char *s) {
    // insert after p
    Node *p;
    for (p = head; p; p = p->next) {
        if (0 <= pos && pos < p->size) {
            break;
        }
        pos -= p->size;
    }

    // log("pos = %d" ,pos);
    if (p == NULL) {
        int len = strlen(s);
        for (int i = 0; i < len; ++i) {
            Append(s[i]);
        }
        return;
    }
    Node *newNode = calloc(1, sizeof(Node));
    for (int i = pos + 1; i < p->size; ++i) {
        newNode->str[(newNode->size)++] = p->str[i];
    }
    p->size = pos + 1;
    Insert(p, newNode);
    Node *temp = newNode;
    // Dump();

    Node *prev = p;
    int len = strlen(s), pp = 0;
    while (pp < len) {
        // block size = B - 1
        newNode = calloc(1, sizeof(Node));
        if (pp + B - 1 < len) {
            newNode->size = B - 1;
            for (int i = 0; i < B - 1; ++i) {
                newNode->str[i] = s[pp + i];
            }
            pp += B - 1;
            Insert(prev, newNode);
        } else {
            newNode->size = len - pp;
            for (int i = 0; i < newNode->size; ++i) {
                newNode->str[i] = s[pp + i];
            }
            Insert(prev, newNode);
            break;
        }
        prev = newNode;
    }
    // Dump();

    // merge
    for (Node *p = head; p; p = p->next) {
        if (p->next != NULL)
            merge(p, p->next);
    }
    log("~~~~~~~~~");
    Dump();
}

void InsertAtHead(char *s) {
    Node *prev, *newNode;
    int len = strlen(s), pp = 0;

    prev = calloc(1, sizeof(struct Node));
    for (; pp < B - 1; ++pp) {
        // Append()
    }

    while (pp < len) {
        // block size = B - 1
        newNode = calloc(1, sizeof(Node));
        if (pp + B - 1 < len) {
            newNode->size = B - 1;
            for (int i = 0; i < B - 1; ++i) {
                newNode->str[i] = s[pp + i];
            }
            pp += B - 1;
            Insert(prev, newNode);
        } else {
            newNode->size = len - pp;
            for (int i = 0; i < newNode->size; ++i) {
                newNode->str[i] = s[pp + i];
            }
            Insert(prev, newNode);
            break;
        }
        prev = newNode;
    }
}

int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &n, &q);
    getchar();
    char ch;
    for (int i = 0; i < n; ++i) {
        ch = getchar();
        Append(ch);
    }
    // Dump();
    while (q--) {
        scanf("%s", cmd);
        scanf("%d", &x);
        --x;
        if (cmd[0] == 'Q') {
            // log("");
            Query(x);
        } else {
            scanf("%s", str);
            if (x == -1) {
                InsertAtHead(str);
            } else {
                InsertString(x, str);
            }
        }
    }
    return 0;
}