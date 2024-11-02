#include <stdio.h>
#include <stdlib.h>

// void f(int a, int b) {
//     printf("%s\t: &a = %p, &b = %p\n", __FUNCTION__, &a, &b);
// }

inline void init() {

}

int main() {
    // int i, j;
    // printf("%s\t: &i = %p, &j = %p\n", __FUNCTION__, &i, &j);
    // f(i, j);
    int *p ;
    p = malloc(sizeof(int) * 10);
    printf("%d %d %d %d %d", p[0], p[1], p[2], p[3], p[4]);
    return 0;
}