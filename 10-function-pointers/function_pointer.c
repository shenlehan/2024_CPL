#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *ptr;

char *names[5] = {
    "ddd", "eee", "hi", "qqq", "qwq"
};

int a[1000] = {1, 2, 3};

int cmp(const void *s1, const void *s2) {
    char *const *str1 = s1;
    char *const *str2 = s2;
    return strcmp(*str1, *str2);
}

int main() {
    // ptr = malloc(sizeof(int) * 100);
    // printf("%d %d %d\n", sizeof(ptr), sizeof ptr, sizeof *ptr);
    // printf("%d %d %d", sizeof(names), sizeof names, sizeof *names);
    // printf("%d %d %d", sizeof(a), sizeof a, sizeof *a);
    char *n = "qwq";
    char **ans = bsearch(&n, names, sizeof names / sizeof *names, sizeof *names, cmp);
    for (int i = 0; i < 5; ++i) printf("%p ", names[i]);
    puts("");

    printf("%p %p\n", names, ans);
    if (ans != NULL)
        printf("%u\n", ans - names);
    else puts("NOT FOUND");
    return 0;
}