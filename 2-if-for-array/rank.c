#include <stdio.h>

int main() {
    int score;
    scanf("%d", &score);
    if (score < 0 || score > 100) {
        printf("Wrong score");
    } else if (score < 60) {
        printf("F");
    } else if (score < 70) {
        printf("D");
    } else if (score < 80) {
        printf("C");
    } else if (score < 90) {
        printf("B");
    } else {
        printf("A");
    }
    return 0;
}