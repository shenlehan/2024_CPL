#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...) 
// do { printf("%s %d ", __FUNCTION__, __LINE__); printf(f, ##args); puts(""); } while (0)

char buffer[5000], ch;
int len, wordlen[10005];
char word[505][505];

const char *reserved[30] = {
    "const", "int", "float", "double",
    "long", "static", "void", "char",
    "extern", "return", "break", "enum",
    "struct", "typedef", "union", "goto"
};

const char *operator[30] = {
    "+", "-", "*", "/",
    "=", "==", "!=", ">=",
    "<=", ">", "<"
};

int ischar(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

int in_reserved(char *str) {
    for (int i = 0; i < 16; ++i) {
        if (!strcmp(str, reserved[i])) {
            return 1;
        }
    }
    return 0;
}

int in_operator(char *str) {
    for (int i = 0; i < 11; ++i) {
        if (!strcmp(str, operator[i])) {
            return 1;
        }
    }
    return 0;
}

int main() {
    while ((ch = getchar()) != '\n') {
        buffer[len++] = ch;
    }
    int pbuffer = 0;
    char *sentence = calloc(1, sizeof(char) * 1024);
    while (pbuffer < len) {
        memset(word, 0, sizeof(word));
        memset(sentence, 0, sizeof(sentence));
        memset(wordlen, 0, sizeof(wordlen));
        int len = 0;
        while (buffer[pbuffer] != ';') {
            sentence[len++] = buffer[pbuffer];
            ++pbuffer;
        }
        ++pbuffer;
        sentence[len] = '\0';
        // printf("Sentence = %s\n", sentence);

        int p = 0, wordcnt = 0;
        while (p < len) {
            while (sentence[p] == ' ')
                ++p;
            while (sentence[p] != ' ') {
                word[wordcnt][wordlen[wordcnt]++] = sentence[p];
                ++p;
            }
            word[wordcnt][wordlen[wordcnt]] = '\0';
            if (word[wordcnt][0] != '\0')
                ++wordcnt;
        }
        // printf("wordcnt:%d Words:##", wordcnt);
        // for (int i = 0; i < wordcnt; ++i) {
        //     printf("##%s##", word[i]);
        // }
        // puts("");
        
        for (int i = 0; i < wordcnt; ++i) {
            if (word[i][0] == '-' && isdigit(word[i][1])) {
                puts("Compile Error");
                log("");
                return 0;
            } else if (isdigit(word[i][0]) && word[i][1] == '.' && (!isdigit(word[i][2]) || word[i][2] == ' ')) {
                log("");
                puts("Compile Error");
                return 0;                
            } else if (isdigit(word[i][0]) && ischar(word[i][1])) {
                log("");
                puts("Compile Error");
                return 0;                  
            } else if (word[i][0] == '-' && ischar(word[i][1])) {
                log("");
                puts("Compile Error");
                return 0;                 
            }

            // operator
            if (!isdigit(word[i][0]) && !ischar(word[i][0]) && word[i][0] != '_') {
                int ok = 0;
                for (int j = 0; j < 11; ++j) {
                    if (word[i][0] == operator[j][0]) {
                        if (strlen(word[i]) >= 2 && strlen(operator[j]) >= 2) {
                            if (word[i][1] != operator[j][1]) {
                                ok = 0;
                            } else {
                                ok = 1;
                            }
                        } else if (strlen(word[i]) == 1 && strlen(operator[j]) == 1) {
                            if (word[i][0] == operator[j][0]) {
                                ok = 1;
                            } else {
                                ok = 0;
                            }              
                        }
                    }
                }
                if (!ok) {
                    log("word[%d][0]=%c###", i, word[i][0]);
                    puts("Compile Error");
                    return 0;                 
                }
            }
        }
    }


    pbuffer = 0;
    while (pbuffer < len) {
        memset(word, 0, sizeof(word));
        memset(sentence, 0, sizeof(sentence));
        memset(wordlen, 0, sizeof(wordlen));
        int len = 0;
        while (buffer[pbuffer] != ';') {
            sentence[len++] = buffer[pbuffer];
            ++pbuffer;
        }
        ++pbuffer;
        sentence[len] = '\0';

        int p = 0, wordcnt = 0;
        while (p < len) {
            while (sentence[p] == ' ')
                ++p;
            while (sentence[p] != ' ') {
                word[wordcnt][wordlen[wordcnt]++] = sentence[p];
                ++p;
            }
            word[wordcnt][wordlen[wordcnt]] = '\0';
            ++wordcnt;
        }
        
        for (int i = 0; i < wordcnt; ++i) {
            if (in_reserved(word[i])) {
                printf("reserved ");
            } else if (isdigit(word[i][0])) {
                if (word[i][1] == '.') {
                    printf("float ");
                } else {
                    printf("integer ");
                }
            } else if (in_operator(word[i])) {
                printf("operator ");
            } else if (word[i][0] != '\0' && (word[i][0] == '_' || ischar(word[i][0]))) {
                printf("variable ");
            }
        }

        puts("");
    }

    return 0;
}