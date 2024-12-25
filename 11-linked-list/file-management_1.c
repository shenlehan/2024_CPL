#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[15];
    struct Node *lson, *rson;
    int sz;
} Node;

Node *root;
int n, q;
char str1[20], str2[20];

void Add(Node *cur, const char *father, const char *son) {
    if (!strcmp(cur->name, father)) {
        if (cur->lson == NULL) {
            cur->lson = malloc(sizeof(Node));
            cur->lson->rson = cur->lson->lson = NULL;
            strcpy(cur->lson->name, son);
        } else {
            cur->rson = malloc(sizeof(Node));
            cur->rson->rson = cur->rson->lson = NULL;
            strcpy(cur->rson->name, son);
        }
        return;
    }
    if (cur->lson) Add(cur->lson, father, son);
    if (cur->rson) Add(cur->rson, father, son);
}

Node *Find(Node *cur, const char *name) {
    if (!strcmp(cur->name, name)) return cur;
    
    Node *res1 = NULL, *res2 = NULL;
    if (cur->lson) res1 = Find(cur->lson, name);
    if (cur->rson) res2 = Find(cur->rson, name);
    
    if (res1) return res1;
    else if (res2) return res2;
    else return NULL;
}

int Query(Node *cur) {
    int ans = 1;
    if (cur->lson) ans += Query(cur->lson);
    if (cur->rson) ans += Query(cur->rson);
    return ans;
}

void Delete(Node *cur, const char *name) {
    if (cur->lson) {
        if (!strcmp(cur->lson->name, name)) {
            cur->lson = NULL;
            return;
        }
        Delete(cur->lson, name);
    }
    if (cur->rson) {
        if (!strcmp(cur->rson->name, name)) {
            cur->rson = NULL;
            return;
        }
        Delete(cur->rson, name);
    }
}

int main() {
    scanf("%d %d", &n, &q);

    root = malloc(sizeof(Node));
    root->lson = root->rson = NULL;
    root->sz = 1;
    strcpy(root->name, "~~~");

    for (int i = 0; i < n; ++i) {
        scanf("%s %s", str1, str2);
        Add(root, str2, str1);
    }

    while (q--) {
        scanf("%s %s", str1, str2);
        if (str1[0] == 'q') {
            Node *p = Find(root, str2);
            printf("%d\n", Query(p));
        } else if (str1[0] == 'r') {
            Delete(root, str2);
        }
    }

    return 0;
}