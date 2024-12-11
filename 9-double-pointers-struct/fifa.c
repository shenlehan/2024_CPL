#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

struct player {
    char name[25];
    int attk, defe, tact;
};

struct team {
    char name[25];
    struct player p[11];
    int ave_attk, ave_defe, ave_tact;
} t[1005];

int n;

int cmp1(const void *t1, const void *t2) {
    struct team *tt1 = (struct team *)t1;
    struct team *tt2 = (struct team *)t2;

    return -(tt1->ave_attk - tt2->ave_attk);
}

int cmp2(const void *t1, const void *t2) {
    struct team *tt1 = (struct team *)t1;
    struct team *tt2 = (struct team *)t2;

    return -(tt1->ave_defe - tt2->ave_defe);
}

int cmp3(const void *t1, const void *t2) {
    struct team *tt1 = (struct team *)t1;
    struct team *tt2 = (struct team *)t2;

    return -(tt1->ave_tact - tt2->ave_tact);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", t[i].name);
        for (int j = 0; j < 11; ++j) {
            scanf("%s %d %d %d", t[i].p[j].name, &t[i].p[j].attk, &t[i].p[j].defe, &t[i].p[j].tact);
            t[i].ave_attk += t[i].p[j].attk;
            t[i].ave_defe += t[i].p[j].defe;
            t[i].ave_tact += t[i].p[j].tact;
        }
    }

    qsort(t, n, sizeof(struct team), cmp1);
    for (int i = 0; i < n; ++i) {
        printf("%s ", t[i].name);
    }
    puts("");

    qsort(t, n, sizeof(struct team), cmp2);
    for (int i = 0; i < n; ++i) {
        printf("%s ", t[i].name);
    }
    puts("");

    qsort(t, n, sizeof(struct team), cmp3);
    for (int i = 0; i < n; ++i) {
        printf("%s ", t[i].name);
    }
    puts("");


    return 0;
}