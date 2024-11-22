#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, len;
char *state;

int main() {
    state = calloc(1, 1005 * sizeof(char));
    scanf("%d %s", &n, state);
    len = strlen(state);
    char *tmp = calloc(1, 1005 * sizeof(char));
    
    while (n--) {
        memcpy(tmp, state, 1005 * sizeof(char));
        for (int pos = 0; pos < len; ++pos) {
            int A = 0, B = 0;
            for (int k = 1; k <= 3; ++k) {
                if (pos + k < len) {
                    if (*(state + pos + k) == 'A') {
                        ++A;
                    } else if (*(state + pos + k) == 'B') {
                        ++B;
                    }
                }

                if (pos - k >= 0) {
                    if (*(state + pos - k) == 'A') {
                        ++A;
                    } else if (*(state + pos - k) == 'B') {
                        ++B;
                    }
                }                
            }

            if (*(state + pos) == '.') {
                if (2 <= A && A <= 4 && B == 0) {
                    *(tmp + pos) = 'A';
                } else if (2 <= B && B <= 4 && A == 0) {
                    *(tmp + pos) = 'B';
                }
            } else if (*(state + pos) == 'A') {
                if (B != 0) {
                    *(tmp + pos) = '.';
                } else if (A >= 5) {
                    *(tmp + pos) = '.';
                } else if (A <= 1) {
                    *(tmp + pos) = '.';
                }
            } else {
                if (A != 0) {
                    *(tmp + pos) = '.';
                } else if (B >= 5) {
                    *(tmp + pos) = '.';
                } else if (B <= 1) {
                    *(tmp + pos) = '.';
                }
            }
        }
        memcpy(state, tmp, 1005 * sizeof(char));
    }
    printf("%s", state);
    return 0;
}