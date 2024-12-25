#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define N 2000005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

typedef struct Node {
    char ch;
    struct Node *next, *prev, *last_same;
} Node;

Node *head, *tail, *last_upper, *last_lower;
int Q, top, size;
char c;
char output[N];

void Append(char c) {
    ++size;
    if (head == NULL) {
        head = malloc(sizeof(Node));
        head->ch = c;
        head->next = head->prev = head->last_same = NULL;
        tail = head;
        if (isupper(c)) {
            last_upper = head;
        } else {
            last_lower = head;
        }
        return;
    }
    Node *newNode = malloc(sizeof(Node));
    newNode->ch = c;
    newNode->prev = tail;
    newNode->next = NULL;
    tail->next = newNode;
    tail = newNode;

    if (isupper(c)) {       
        if (last_upper == NULL) last_upper = newNode;
        newNode->last_same = last_upper;
        last_upper = newNode;

    } else {
        if (last_lower == NULL) last_lower = newNode;
        newNode->last_same = last_lower;
        last_lower = newNode;
    }
}

void Delete(Node *pos) {
    if (pos == NULL) return;

    Node *prev = pos->prev;
    Node *next = pos->next;
        
    if (pos != head) prev->next = next;
    if (pos != tail) next->prev = prev;

    if (prev != NULL) tail = prev;

    if (isupper(pos->ch)) last_upper = pos->last_same;
    else last_lower = pos->last_same;
    --size;

    if (size == 0) head = tail = NULL;
    
    free(pos);
}

void Query(int len) {
    top = 0;
    for (Node *p = tail; top < len && p != NULL; ++top, p = p->prev) {
        output[top] = p->ch;
    }
    
    for (int i = top - 1; i >= 0; --i) putchar(output[i]);
    puts(""); 

}

void Print() {
    log("######");
    for (Node *p = head; p; p = p->next) {
        log("%c", p->ch);
    }
    log("######");
}


int main() {
    scanf("%d", &Q);
    getchar();
    while (Q--) {
        
        while ((c = getchar()) != '\n') {

            if (c == '?') {
                int x;
                scanf("%d", &x);
                Query(x);
                getchar();
                break;
            }

            if (c == 'm') {
                Delete(last_lower);
            } else if (c == 'M') {
                // printf("Now tail is %c\n", tail->ch);
                Delete(last_upper);
                
            } else {
                Append(c);
            }
            // Print();
        }
    }
    return 0;
}