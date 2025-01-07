#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); } while (0)

typedef struct Node {
    char c;
    struct Node *next;
} Node;

typedef struct LinkList {
    Node *head, *tail;
} LL;

LL *ll=NULL;
char str[N]={0}, orig[105][N]={0}, repl[105][N];
int n=0, m=0;

void printList(LL *list) {
    for (Node *p = list->head; p; p = p->next) {
        printf("%c", p->c);
    }
    puts("");
}

LL *build(const char *s) {
    LL *res=NULL;
    Node *newNode;
    res = calloc(1, sizeof(LL));
    for (const char *p = s; *p; ++p) {
        if (res->head == NULL) {
            res->head = calloc(1, sizeof(Node));
            res->head->c = *p;
            res->tail = res->head;
        } else {
            newNode = calloc(1, sizeof(Node));
            newNode->c = *p;
            res->tail->next = newNode;
            res->tail = newNode;
        }
    }
    return res;
}

void print(Node *pos) {
    for (Node *p = pos; p; p = p->next) {
        printf("%c",p->c);
    }
    puts("");
}

Node *match(Node *pos, int id) {
    int len = strlen(orig[id]);
    int i=0;
    Node *p=NULL;
   
    // log("");
    //  print(pos);
   // log("i=%d\n",i);
    for (p = pos; p && i < len - 1; ++i, p = p->next) {
        //log("i=%d orig[%d]=%s",i,id,orig[id]);
        if (p->c != orig[id][i]) return NULL;
    }
    // 我把最后一个元素特殊处理，这样可以直接返回尾指针，就不用再遍历一次
    // 对啊 但为什么会影响下面
    if (!p) return NULL;
    if (p->c != orig[id][i]) return NULL;
    else return p;
}

void replace(int id) {
    Node *end, *prev;
    LL *temp;
    log("try to find oir[%d]=%s in ",id,orig[id]);
    printList(ll);
    for (Node *p = ll->head; p; prev = p, p = p->next) {
       
        end = match(p, id);
        if (end == NULL) continue;
        log("##############FOUND %s\n",orig[id]);
        temp = build(repl[id]);
        // printList(temp);

        if (prev == NULL) {
            temp->tail->next = end->next;
            ll->head = temp->head;
        } else {
            temp->tail->next = end->next;
            prev->next = temp->head;
        }
       // log("");
        // printList(ll);
        p = end;
    }
}

int main() {
    freopen("rna.txt", "r", stdin);
    scanf("%s %d %d", str, &n, &m);
    ll = build(str);
    // printList(ll);
    for (int i = 0; i < n; ++i) {
        scanf("%s %s", orig[i], repl[i]);
    }
    while (m--) {
        for (int i = 0; i < n; ++i) {
            // log("");
            replace(i);
        }
        log("TMP:");
        printList(ll);
    }
    log("FINAL:\n");
    printList(ll);
    return 0;
}