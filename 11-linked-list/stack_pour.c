#include <stdio.h>
#include <stdlib.h>
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

int n, m;

typedef struct Node {
    int num;
    struct Node *next;
} Node;

typedef struct Stack {
    int size;
    Node *top, *bottom;
} Stack;

Node *newNode;
Stack s[1000005];
int out[1000005];

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        newNode = malloc(sizeof(Node));
        newNode->num = i;
        newNode->next = NULL;
        s[i].top = s[i].bottom = newNode;
        s[i].size = 1;
    }

    int x, y;
    while (m--) {
        scanf("%d %d", &x, &y);
        // add s[x] to s[y]
        if (!s[x].size) continue;
        
        for (Node *temp = s[x].top, *next; temp != NULL; temp = next) {
            next = temp->next;
            temp->next = s[y].top;
            s[y].top = temp;
        }

        s[y].size += s[x].size;
        s[x].size = 0;
        s[x].top = s[x].bottom = NULL;
    }

    for (int i = 1; i <= n; ++i) {
        if (!s[i].size) {
            puts("0");
        } else {
            int len = 0;
            for (Node *temp = s[i].top; temp != NULL; temp = temp->next) {
                out[len++] = temp->num;
            }
            for (int i = 0; i < len; ++i) printf("%d ", out[i]);
            puts("");
        }
    }
    return 0;
}