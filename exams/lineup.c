#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;
    int x, y;
    struct Node *down, *right;
} Node;

int n, m, q;
int x1, y1, x2, y2, x3, y3, x4, y4, a;
Node *line[2505];

void Init() {
    Node *newNode;
    for (int i = 1; i <= n; ++i) {
        Node *prev;
        for (int j = 1; j <= m; ++j) {
            newNode = malloc(sizeof(Node));
            newNode->num = i * m + j;
            newNode->x = i, newNode->y = j;
            if (j == 1) {
                line[i] = newNode;
            } else {
                prev->right = newNode;
            }

            // if (j != 1) {
            //     printf("Prev->num = %d\n", prev->num);
            // }
            prev = newNode;
            // printf("Now i = %d, j = %d, newNode->num = %d\n", i, j, newNode->num);

            if (j == m) {
                newNode->right = NULL;
            }
            // printf("##Prev->num = %d\n", prev->num);
        }
    }

    Node *temp[2505];
    for (int i = 1; i <= n; ++i) temp[i] = line[i];
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n; ++i) {

            if (i < n) temp[i]->down = temp[i + 1];
            else temp[i]->down = NULL;
            
            temp[i] = temp[i]->right;
        }
    }
}

void Update(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    if (x1 == 1) {

    }

}

int main() {
    scanf("%d %d %d", &n, &m, &q);

    Init();

#if 0
    for (int i = 1; i <= n; ++i) {
        Node *temp = line[i];
        for (int j = 1; j <= m; ++j) {
            printf("%d ", temp->num);
            temp = temp->right;
        }
        puts("");
    }
#endif

#if 0
    Node *temp1 = line[1], *temp2 = line[1];
    for (int i = 1; i <= m; ++i) {
        temp1 = temp2;
        while (temp1) {
            printf("%d ", temp1->num);
            temp1 = temp1->down;
        }
        temp2 = temp2->right;
        puts("OK HERE");

    }
#endif

    while (q--) {
        scanf("%d %d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &a);
        Update(x1, y1, x2, y2, x3, y3, x4, y4);

    }



    return 0;
}