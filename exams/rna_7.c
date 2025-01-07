#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 105
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct node {
    char ch;
    struct node *next;
} Node;

typedef struct LinkList {
    Node *head, *tail;
} LinkList;

LinkList *LL;

int n, m;
char orgi[N][N], repl[N][N], rna[10005];

void print(LinkList *ll) {
	Node *p =NULL;
    for (p = ll->head; p; p = p->next) {
        printf("%c", p->ch);
    }
    puts("");
}
void freeList(LinkList *ll) {
	Node *p =NULL;
	Node *t =NULL;
    for (p = ll->head; p;) {
    	 t = p->next;
         free(p);
         p = t;
    }
}
LinkList *build(const char *str) {
    LinkList *res = calloc(1, sizeof(LinkList));
    Node *newNode;
    const char *p=NULL;
    for (p = str; *p; ++p) {
        if (res->head == NULL) {
            res->head = calloc(1, sizeof(Node));
            res->head->ch = *p;
            res->tail = res->head;
        } else {
            newNode = calloc(1, sizeof(Node));
            newNode->ch = *p;
            res->tail->next = newNode;
            res->tail = newNode;
        }
    }
    return res;
}

Node *match(Node *pos, int id) {
    Node *p = pos;
    int len = strlen(orgi[id]), i;
    for (i = 0; p != NULL && i < len - 1; ++i, p = p->next) {
        if (p->ch != orgi[id][i]) return NULL;
    }
    if (!p) return NULL;
    if (p->ch != orgi[id][i]) return NULL;
    else return p;
}

void replace(int id) {
    int len = strlen(orgi[id]);
    Node *p =NULL;
    Node *prev =NULL;
    Node *end = p;
    for (p = LL->head; p; ) {
        // print(LL);
        end =match(p, id);
        if (end) {
            LinkList *temp = build(repl[id]);
            int i=0;
            for (i = 0; i < len - 1; ++i) {
                //end = end->next;
                Node *t=end->next;
                free(end);
                end=t;
            }
            temp->tail->next = end->next;
            free(end);
            if (p == LL->head) {
                LL->head = temp->head;
            } else {
               // Node *prev = LL->head;
                //for (; prev->next != p; prev = prev->next);
                //prev->next = temp->head;
                prev->next=temp->head;
            }
            
           // p = temp->tail;
            p = temp->tail->next;
            prev=temp->tail;
            free(temp);
        } else {
        	prev=p;
            p = p->next;
        }
        
    }
}

int main() {
    //freopen("rna.txt", "r", stdin);
    scanf("%s %d %d", rna, &n, &m);
    int i=0;
    for (i = 0; i < n; ++i) {
        scanf("%s %s", orgi[i], repl[i]);
    }
    LL = build(rna);
    while (m--) {
    	int i=0;
        for ( i = 0; i < n; ++i) {
            replace(i);
        }
    }
    print(LL);
    freeList(LL);
    return 0;
}