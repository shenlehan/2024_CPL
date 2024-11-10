#include <stdio.h>
#include <stdlib.h>

int n, c, len;
char op[10];

struct node {
    int n;
    struct node *nxt, *prev;
} *front, *tail, *new_node;

void In(int n) {
    ++len;

    if (tail == NULL) {
        tail = calloc(1, sizeof(struct node));
        tail->n = n;
        front = tail;
        return;
    }

    new_node = calloc(1, sizeof(struct node));
    new_node->prev = tail;
    new_node->n = n;
    tail->nxt = new_node;
    tail = new_node;
}

void Out() {
    --len;
    new_node = front->nxt;
    printf("%d\n", front->n);
    free(front);
    front = new_node;
}


void Cat() {
    if (len == 0) {
        printf("0 []");
        return;
    }

    printf("%d [%d", len, front->n);
    for (new_node = front->nxt; new_node != NULL; new_node = new_node->nxt) {
        printf(",%d", new_node->n);
    }
    puts("]");
}

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%s", op);
        if (op[0] == 'I' && op[1] == 'n') {
            scanf(" %d ", &c);
            In(c);
        } else if (op[0] == 'O' && op[1] == 'u') {
            Out();
        } else if (op[0] == 'C') {
            Cat();
        }
    }
    return 0;
}