#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define B 4
#define N 100005
#define log(f, args...)  do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    char cont[B+1];
    int size;
    struct Node *prev, *next;
} Node;

Node *head, *tail, *newNode;
int n, q;
char ch, comd[5], str[N];
void DumpNode(Node *p){
    printf("size=%d ",p->size);
    for (int i = 1; i <= p->size; ++i) {
            printf("%c", p->cont[i]);
    }
    printf("\n");
}
void Dump() {
    for (Node *p = head; p; p = p->next) {
#if 1
        DumpNode(p);
#else        
        //log("p->size=%d",p->size);
        for (int i = 1; i <= p->size; ++i) {
            printf("%c", p->cont[i]);
        }
        puts("");
#endif        
    }
}
void Append(char c) {
    if (head == NULL) {
        head = malloc(sizeof(Node));
        head->prev = head->next = NULL;
        head->cont[1] = c;
        head->size = 1;
        tail = head;
        return;
    }
    
    if (tail->size < B) {
        ++(tail->size);
        tail->cont[tail->size] = c;
        return;
    }

    newNode = malloc(sizeof(Node));
    newNode->size = 1;
    newNode->cont[1] = c;
    newNode->prev = tail;
    tail->next = newNode;
    newNode->next = NULL;
    tail = newNode;
}

void Query(int pos) {
    //log("######pos=%d",pos);
    int step=0;
    for (Node *p = head; p; p = p->next) {
       // DumpNode(p);
        if(step<=pos&&(step+p->size)>pos)
            printf("%c\n",p->cont[1+pos-step]);
        step+=p->size;
        //log("pos=%d",pos);
    }
}

void Insert(int pos, const char *str) {
    Node *p;
   // log("pos=%d str=%s",pos,str);
    for (p = head; p; p = p->next) {
        if (1 <= pos && pos <= p->size) {
            break;
        }
        pos -= p->size;
    }

    // insert after cur->cont[pos]
    newNode = malloc(sizeof(Node));
    memset(newNode, 0, sizeof(Node));
   // log("pos=%d\n",pos);
    for (int i = pos + 1; i <= p->size; ++i) {
        newNode->cont[++(newNode->size)] = p->cont[i];
    }
    newNode->next = p->next;
    if (p->next) p->next->prev = newNode;
    p->next = newNode;
    newNode->prev = p;
    p->size = pos;
    //Dump();
    // insert string
    int len = strlen(str ), strPos = 0;
    Node *prev = p;
    while (strPos < len) {
        newNode = calloc(1, sizeof(Node));
        if (strPos + B - 1 <= len) {
            for (int i = strPos; i <= strPos + B - 1; ++i) {
                newNode->cont[++(newNode->size)] = str[i];
                //log("###########");
                //DumpNode(newNode);
            }
            strPos += B;
        } else {
            for (int i = strPos; i < len; ++i) {
                newNode->cont[++(newNode->size)] = str[i];
               // log("**********");
                //DumpNode(newNode);
            }
            strPos = len + 1;
        }
        newNode->prev = prev;
        newNode->next = prev->next;
        prev->next->prev = newNode;
        prev->next = newNode;
        prev = newNode;
    }
   // Dump();
#if 1
     // merge
//    DumpNode(newNode);
    if (newNode->next && newNode->size + newNode->next->size <= B) {
        // log("");
        Node *merge = calloc(1, sizeof(Node));
        for (int i = 1; i <= newNode->size; ++i) {
            merge->cont[++(merge->size)] = newNode->cont[i];
        }
        // log("");
        for (int i = 1; i <= newNode->next->size; ++i) {
            merge->cont[++(merge->size)] = newNode->next->cont[i];
        }       
        // log("");
        newNode->prev->next = merge;
        merge->prev = newNode->prev;
        if (newNode->next) merge->next = newNode->next->next;
        if (newNode->next->next) newNode->next->next->prev = merge; 
    }
    // Dump();
#endif
}


int main() {
    freopen("data.in.txt", "r", stdin);
    scanf("%d %d", &n, &q);
    getchar();
    for (int i = 1; i <= n; ++i) {
        ch = getchar();
        Append(ch);
        //Dump();
    }
    //Dump();
#if 1
    int x;
    while (q--) {
        scanf("%s", comd);
        if (comd[0] == 'Q') {
            scanf("%d", &x);
            //log("x=%d\n",x);
            Query(x);
        } else {
#if 1            
            scanf("%d %s", &x, str + 1);
            Insert(x, str + 1);
            //Dump();
#endif            
        }
    }
#endif    
    return 0;
}