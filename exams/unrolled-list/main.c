#include <stdio.h>
#include "list.h"
#include <string.h>
#include <stdlib.h>
#define log(f, args...) do { printf("%s %d ", __FUNCTION__, __LINE__); printf(f, ##args); printf("\n"); } while (0)

struct Node {
    char name[1000];
    char author[1000];
    double price;
    struct list_head conn_list;
    struct Node* next;
    struct Node* prev;
};

struct list_head head = LIST_HEAD_INIT(head);
int n;
char line[500];
const char *delimeter = " ";

int main() {
    freopen("data0.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        getchar();
        gets(line);
        getchar();
        // log("%s", line);
        int len = strlen(line);
        // log("%d", len);
        struct Node *newNode = malloc(sizeof(struct Node));
        memset(newNode, 0, sizeof(struct Node));
        scanf(" %lf", &newNode->price);
        char *p = strtok(line, delimeter);
        int f = 0;
        // log("%p", p);
        while (p != NULL) {
            // log("%s", p);
            if (!strcmp(p, "by")) {
                f = 1;
                p = strtok(NULL, delimeter);
                continue;
            }
            if (f == 0) {
                strcat(&newNode->name, p);
                strcat(&newNode->name, " ");
            } else {
                strcat(&newNode->author, p);
                strcat(&newNode->author, " ");
            }
            p = strtok(NULL, delimeter);
        }
        list_add_tail(&newNode->conn_list, &head);
        
        log("author:%s name:%s price:%lf", newNode->author,newNode->name, newNode->price);
    }

    struct list_head *pos, *n;
    list_for_each_safe(pos, n, &head) {
        struct Node *temp = list_entry(pos, struct Node, conn_list);
        log("%s %s %lf", temp->author,temp->name, temp->price);
    }

    return 0;
}