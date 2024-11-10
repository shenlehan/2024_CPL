#include <stdio.h>
#include <stdlib.h>

int n;
char op[10], c;

struct node {
    char ch;
    struct node *nxt;
} *top, *new_node;

void push(char ch) {
    if (top == NULL) {
        top = calloc(1, sizeof(struct node));
        top->ch = ch;
        return;
    }

    new_node = calloc(1, sizeof(struct node));
    new_node->ch = ch;
    new_node->nxt = top;
    top = new_node;
}

void pop() {
    if (top == NULL) {
        puts("Empty");
        return;
    }

    new_node = top->nxt;
    free(top);
    top = new_node;
}

void get_top() {
    if (top == NULL) {
        puts("Empty");
        return;
    }

    printf("%c\n", top->ch);
}

void print() {
    if (top == NULL) {
        puts("Empty");
        return;
    }

    struct node *tmp = top;
    for (; tmp != NULL; tmp = tmp->nxt) {
        printf("| %c |\n", tmp->ch);
    }
    puts("|===|");
}

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%s", op);
        if (op[0] == 'p' && op[1] == 'u') {
            scanf(" %c ", &c);
            push(c);
        } else if (op[0] == 'p' && op[1] == 'o') {
            pop();
        } else if (op[0] == 't') {
            get_top();
        } else {
            print();
        }
    }
    return 0;
}