/**
 * This version uses the "strtok" 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

const char *delimeter = ";";

int T;
char *s1, *s2;
int ds1, ds2, size;

void interleaveString(char *s, char *t, int sz) {
    char *s3 = calloc(1, sizeof(char) * (sz + 10)); // bigger
    int ps = 0, pt = 0, len = 0;
    while (ps < strlen(s) && pt < strlen(t) && len < sz - 1) {
        int i, j;
        for (i = 0; i < ds1 && ps + i < strlen(s) && len < sz - 1; ++i) {
            s3[len++] = s[ps + i];
        }
        ps += i;

        for (j = 0; j < ds2 && pt + j < strlen(t) && len < sz - 1; ++j) {
            s3[len++] = t[pt + j];
        }
        pt += j;     
    }
    while (ps < strlen(s) && len < sz - 1) {
        s3[len++] = s[ps++];
    }
    while (pt < strlen(t) && len < sz - 1) {
        s3[len++] = t[pt++];
    }
    s3[len] = '\0';
    puts(s3);
    free(s3);
    return;
}

int main() {
    scanf("%d", &T);
    s1 = calloc(1, sizeof(char) * 1005);
    s2 = calloc(1, sizeof(char) * 1005);
    char *_ds1 = calloc(1, sizeof(char) * 10);
    char *_ds2 = calloc(1, sizeof(char) * 10);
    char *_size = calloc(1, sizeof(char) * 10);
    getchar();
    while (T--) {
        int l1 = 0, l2 = 0;
        char ch;
        char *line = calloc(1, sizeof(char) * 5000);
        fgets(line, 5000, stdin);
        line[strlen(line) - 1] = 0;
        // printf("len = %d\n", strlen(line));
        // for (int i = 0; i < strlen(line); ++i) {
        //     printf("line[%d] = ##%c##\n", i, line[i]);
        // }
        // // strtok(line, delimeter);
        s1 = strtok(line, delimeter);
        printf("line now is %s\n", line);
        // s2 = strtok(NULL, delimeter);
        // _ds1 = strtok(NULL, delimeter);
        // _ds2 = strtok(NULL, delimeter);
        // _size = strtok(NULL, delimeter);

        // ds1 = atoi(_ds1);
        // ds2 = atoi(_ds2);
        // size = atoi(_size);

        // printf("s1 = %s, s2 = %s, ds2 = %s, ds2 = %s, size = %s\n", s1, s2, _ds1, _ds2, _size);
        // interleaveString(s1, s2, size);
    }
    free(s1);
    free(s2);
    return 0;
}