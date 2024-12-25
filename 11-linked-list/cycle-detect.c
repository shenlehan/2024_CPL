#include <stdio.h>
#define N 100005

typedef struct node {
    char contents[25];
    struct node *next;
} node;

node a[N];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1, k; i <= n; ++i) {
        scanf("%s %d", a[i].contents, &k);
        if (1 > k || k > n) continue;
        a[i].next = &a[k];
    }
    
    node *t = &a[1], *h = &a[1];
    do {
        t = t->next;
        h = h->next;
        if (h != NULL) h = h->next;
    } while (t != h && h != NULL);

    if (h == NULL) {
        puts("-1");
        return 0;
    }

    t = &a[1];
    while (t != h) {
        t = t->next;
        h = h->next;
    }
    printf("%s", t->contents);

    return 0;
}