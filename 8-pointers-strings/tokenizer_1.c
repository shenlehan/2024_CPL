#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...)  
// do { printf("%s %d ", __FUNCTION__, __LINE__); printf(f, ##args); puts(""); } while (0)

char buffer[5000], ch;
int len, wordlen[10005];
char word[505][505];
int wordcnt = 0;
int cut[100005];

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

char tmp[1005];

int main() {
    // freopen("test.txt", "r", stdin);
    while (scanf("%s", tmp) != EOF) {
        int k;
        int len = 0;
        int flag = 0;
        if (!strcmp(tmp, ";")) {
            ++cut[wordcnt];
            continue;
        }
        ++wordcnt;
        
        for (k = 0; k < strlen(tmp); ++k) {
            if (tmp[k] == ';' && k != 0) {
                // printf("word[wordcnt] = %s\n", word[wordcnt]);
                // printf("FINISHED\n");
                word[wordcnt][len] = '\0';
                len = 0;
                ++cut[wordcnt];
                wordcnt++;
                
                flag = 1;
            } else if (tmp[k] != ';') {
                word[wordcnt][len++] = tmp[k];
             
            }
        }
    }
    
    // puts("###############");
    // for (int i = 1; i <= wordcnt; ++i) {
    //     printf("%s\n", word[i]);
    // }
    // puts("");    
    
    for (int i = 1; i <= wordcnt; ++i) {
        if (word[i][0] == '\0')
            continue;
        
        if (!(word[i][0] == '_' || ischar(word[i][0])) && ischar(word[i][1])) {
            puts("Compile Error");
            log("");
            return 0;
        } else if (isdigit(word[i][0]) && word[i][1] == '.' && !isdigit(word[i][2])) {
            puts("Compile Error");
            log("");
            return 0;
        } else if (isdigit(word[i][1]) && (word[i][0] == '-' || word[i][0] == '+')) {
            puts("Compile Error");
            log("");
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

    
    for (int i = 1; i <= wordcnt; ++i) {
        // log("%d", i);
        if (word[i][0] == '\0') {
            continue;
        }
        if (in_reserved(word[i])) {
            printf("reserved ");
        } else if (isdigit(word[i][0])) {
            int f = 0;
            for (int k = 0; k < strlen(word[i]); ++k) {
                if (word[i][k] == '.') {
                    printf("float ");
                    f = 1;
                    break;
                }
            }
            if (!f) {
                printf("integer ");
            }
        } else if (in_operator(word[i])) {
            printf("operator ");
        } else if (word[i][0] != '\0' && (word[i][0] == '_' || ischar(word[i][0]))) {
            printf("variable ");
        }
        while (cut[i]--)
            puts("");
    }
    return 0;
}