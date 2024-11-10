#include <stdio.h>
#include <stdlib.h>
#define N 1005

int n, c, q[N], front, tail;
char op[10];

void In(int n) {
    q[tail++] = n;
}

void Out() {
    printf("%d\n", q[front]);
    ++front;
}


void Cat() {
    if (tail - front == 0) {
        printf("0 []");
        return;
    }

    printf("%d [%d", tail - front, q[front]);
    for (int i = front + 1; i < tail; ++i) {
        printf(",%d", q[i]);
    }
    puts("]");
}

int main() {
    front = tail = 0;
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