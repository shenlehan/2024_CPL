#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)
#define N 1000005

typedef struct Node {
    char cont[1005];
    struct Node *next;
} Node;

Node *list[N * 2];
int m, q;
char str[1005];

int hash(char *s){
    int len = strlen(s);
    int ret = 0;
    for(int i = 0; i < len; i++) ret = (ret + s[i] * (i + 1)) % N;
    return ret;

}


int main() {
    scanf("%d %d", &m, &q);

    for (int i = 0; i < m; ++i) {
        scanf("%s", str);
        int v = hash(str);

        if (list[v] == NULL) {
            list[v] = malloc(sizeof(Node));
            list[v]->next = NULL;
            strcpy(list[v]->cont, str);
        } else {
            Node *p;
            for (p = list[v]; p->next != NULL; p = p->next);
            Node *q = malloc(sizeof(Node));
            strcpy(q->cont, str);
            q->next = NULL;
            p->next = q;
        }
    }

    while (q--) {
        scanf("%s", str);
        int v = hash(str);
        if (list[v] == NULL) puts("No");
        else {
            int f = 0;
            for (Node *p = list[v]; p; p = p->next) {
                if (strcmp(p->cont, str) == 0) {
                    puts("Yes");
                    f = 1;
                    break;
                }
            }
            if (!f) puts("No");
        }
    }

    return 0;
}