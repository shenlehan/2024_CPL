#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define log(f, args...) do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

const char *delimeter = " ";
char *line;

int main() {
    line = calloc(1, sizeof(char) * 5005);
    fgets(line, 5005, stdin);
    
    char *word = strtok(line, delimeter);
    while (word != NULL) {
        putchar(toupper(*word));
        for (int i = 1; i < strlen(word); ++i) {
            putchar(tolower(*(word + i)));
        }
        putchar(' ');   
        word = strtok(NULL, delimeter);
    }

    free(line);
    return 0;
}