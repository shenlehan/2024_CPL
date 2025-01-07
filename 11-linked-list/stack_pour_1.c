#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); printf("\n"); } while(0)

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkList {
    int size;
    Node *head, *tail;
} LL;

LL *stack[N];
int n, m;
int out[N], cnt;

void init() {
    for (int i = 0; i <= n; ++i) {
        stack[i] = (LL *)malloc(sizeof(LL));
        stack[i]->head = calloc(1, sizeof(Node));
        stack[i]->tail = stack[i]->head;
        stack[i]->head->data = i;
        stack[i]->size = 1;
    }
}

void add(int x, int y) {
    Node *next;
    if(!stack[x]->size) return;
    for (int i = 0; i < stack[x]->size; ++i) {
        next = stack[x]->head->next;
        stack[x]->head->next = stack[y]->head;
        stack[y]->head = stack[x]->head;
        stack[x]->head = next;
        ++stack[y]->size;
    }
    stack[x]->size = 0;
}

void print() {
    for (int i = 1; i <= n; ++i) {
        if (!stack[i]->size) {
            printf("0\n");
            continue;
        }
        for (Node *p = stack[i]->head; p; p = p->next) {
            out[cnt++] = p->data;
        }
        for (int j = cnt - 1; j >= 0; --j) {
            printf("%d ", out[j]);
        }
        printf("\n");
        cnt = 0;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    int x, y;
    init();
    while (m--) {
        scanf("%d %d", &x, &y);
        add(x, y);
    }
    print();
    return 0;
}