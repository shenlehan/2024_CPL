#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 2000005
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

struct Node {
    char c;
    struct Node *next, *prev, *last_same;
} *head, *tail, *last_upper, *last_lower;

int Q, x, size, top;
char comd[N];
char output[N];

void Append(char c) {
    ++size;
    if (head == NULL) {
        head = malloc(sizeof(struct Node));
        head->c = c;
        head->last_same = NULL;
        head->next = head->prev = NULL;
        tail = head;
        if (isupper(c)) {
            last_upper = head;
        } else {
            last_lower = head;
        }
        return;
    }

    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->prev = tail;
    newNode->next = NULL;
    newNode->c = c;
    tail->next = newNode;
    if (isupper(c)) {
        newNode->last_same = last_upper;
        last_upper = newNode;
    } else {
        newNode->last_same = last_lower;
        last_lower = newNode;
    }
    tail = newNode;
}

void Delete(struct Node *pos) {
    if (pos == NULL) return;
    struct Node *prev = pos->prev;
    struct Node *next = pos->next;
        
    if (pos == head) {
        head = head->next;
        if (head != NULL) head->prev = NULL;
    } else if (pos == tail) {
        tail = tail->prev;
        if (tail != NULL) tail->next = NULL;
    } else {
        prev->next = next;
        if(next != NULL) next->prev = prev;
    }

    if (isupper(pos->c)) last_upper = pos->last_same;
    else last_lower = pos->last_same;
    --size;

    if (size == 0) head = tail = NULL;
    
    free(pos);
}

void Query(int len) {
    top = 0;
    if (tail == NULL) return; // pos 1
    for (struct Node *p = tail; top < len && p != NULL; ++top, p = p->prev) {
        output[top] = p->c;
    }
    
    for (int i = top - 1; i >= 0; --i) putchar(output[i]);
    puts(""); 

}

int main() {
    scanf("%d", &Q);
    while (Q--) {
        scanf("%s", comd);
        if (comd[0] == '?') {
            scanf("%d", &x);
            Query(x); 
        } else {
            for (int i = 0; comd[i]; ++i) {
                if (comd[i] == 'm') {
                    Delete(last_lower);
                } else if (comd[i] == 'M') {
                    // log("last_upper = %c", last_upper->c);
                    Delete(last_upper);
                } else {
                    Append(comd[i]);
                }
            }
        }
    }
    return 0;
}