#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define B 500
#define N 100005
#define log(f, args...)  do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    char cont[B];
    int size;
    struct Node *prev, *next;
} Node;

Node *head, *tail, *newNode;
int n, q;
char ch, comd[5], str[N];

void Append(char c) {
    if (head == NULL) {
        head = malloc(sizeof(Node));
        head->prev = head->next = NULL;
        head->cont[1] = c;
        head->size = 1;
        tail = head;
        return;
    }
    
    if (tail->size < B) {
        ++(tail->size);
        tail->cont[tail->size] = c;
        return;
    }

    newNode = malloc(sizeof(Node));
    newNode->size = 1;
    newNode->cont[1] = c;
    newNode->prev = tail;
    tail->next = newNode;
    newNode->next = NULL;
    tail = newNode;
}

void Query(int pos) {
    for (Node *p = head; p; p = p->next) {
        if (1 <= pos && pos <= p->size) {
            printf("%c\n", p->cont[pos]);
        }
        pos -= p->size;
    }
}

void Insert(int pos, const char *str) {
    Node *p;
    for (p = head; p; p = p->next) {
        if (1 <= pos && pos <= p->size) {
            break;
        }
        pos -= p->size;
    }

    // insert after cur->cont[pos]
    newNode = malloc(sizeof(Node));
    for (int i = pos + 1; i <= p->size; ++i) {
        newNode->cont[++(newNode->size)] = p->cont[i];
    }
    newNode->next = p->next;
    if (p->next) p->next->prev = newNode;
    p->next = newNode;
    newNode->prev = p;
    p->size = pos;

    // insert string
    int len = strlen(str + 1), strPos = 1;
    Node *prev = p;
    while (strPos <= len) {
        newNode = calloc(1, sizeof(Node));
        if (strPos + B - 1 <= len) {
            for (int i = strPos; i <= strPos + B - 1; ++i) {
                newNode->cont[++(newNode->size)] = str[i];
            }
            strPos += B;
        } else {
            for (int i = strPos; i <= len; ++i) {
                newNode->cont[++(newNode->size)] = str[i];
            }
            strPos = len + 1;
        }
        newNode->prev = prev;
        newNode->next = prev->next;
        prev->next->prev = newNode;
        prev->next = newNode;
        prev = newNode;
    }
#if 0
    log("");
    // merge
    if (newNode->next && newNode->size + newNode->next->size <= B) {
        log("");
        Node *merge = calloc(1, sizeof(Node));
        for (int i = 1; i <= newNode->size; ++i) {
            merge->cont[++(merge->size)] = newNode->cont[i];
        }
        log("");
        for (int i = 1; i <= newNode->next->size; ++i) {
            merge->cont[++(merge->size)] = newNode->next->cont[i];
        }       
        log("");
        newNode->prev->next = merge;
        merge->prev = newNode->prev;
        if (newNode->next) merge->next = newNode->next->next;
        if (newNode->next->next) newNode->next->next->prev = merge; 
    }
#endif
}

int main() {
    scanf("%d %d", &n, &q);
    getchar();
    for (int i = 1; i <= n; ++i) {
        ch = getchar();
        Append(ch);
    }
    // for (Node *p = head; p; p = p->next) {
    //     for (int i = 1; i <= p->size; ++i) {
    //         printf("%c", p->cont[i]);
    //     }
    //     puts("");
    // }

    int x;
    while (q--) {
        scanf("%s", comd);
        if (comd[0] == 'Q') {
            scanf("%d", &x);
            Query(x);
        } else {
            scanf("%d %s", &x, str + 1);
            Insert(x, str);
        }
    }

    return 0;
}