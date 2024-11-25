#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...)  
// do { printf("%s %d ", __FUNCTION__, __LINE__); printf(f, ##args); puts(""); } while (0)

const char *reserved[30] = {
    "const", "int", "float", "double",
    "long", "static", "void", "char",
    "extern", "return", "break", "enum",
    "struct", "typedef", "union", "goto"
};

const char *oper[11] = {
    "+", "-", "*", "/",
    "=", "==", "!=", ">=",
    "<=", ">", "<"
};

int ischar(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

int isreserved(char *str) {
    for (int i = 0; i < 16; ++i) {
        if (!strcmp(str, reserved[i])) {
            return 1;
        }
    }
    return 0;
}

int isoperator(char *str) {
    for (int i = 0; i < 11; ++i) {
        if (str[0] == oper[i][0]) {
            if (strlen(str) == 2 && strlen(oper[i]) == 2) {
                if (str[1] == oper[i][1]) {
                    return 1;
                }
            } else if (strlen(str) == 1 && strlen(oper[i]) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

char *s;
char ans[200005];

void process(char *str) {
    log("str = %s###", str);
    int is_dig = 0, is_float = 0, is_var = 0, is_op = 0, is_reser = 0;
    if (!strlen(str)) {
        return;
    }
    if (isdigit(str[0])) {
        is_dig = 1;
        int dot = 0;
        for (int k = 0; k < strlen(str); ++k) {
            if (str[k] == '.') {
                is_float = 1;
                is_dig = 0;
                ++dot;
            }
            if (!isdigit(str[k]) && str[k] != '.') {
                puts("Compile Error");
                log("");
                exit(0);
            }
            if (dot >= 2) {
                log("");
                puts("Compile Error");
                exit(0);                        
            }
        }
    } else if (str[0] == '.') {
        int dot = 0;
        for (int k = 0; k < strlen(str); ++k) {
            if (str[k] == '.') {
                is_float = 1;
                ++dot;
            }
            if (!isdigit(str[k]) && str[k] != '.') {
                puts("Compile Error");
                log("");
                exit(0);
            }
            if (dot >= 2) {
                log("");
                puts("Compile Error");
                exit(0);                        
            } 
        }
        if (strlen(str) == 1) {
            puts("Compile Error");
            exit(0);
        }            
    } else if (ischar(str[0]) || str[0] == '_') {
        if (isreserved(str)) {
            is_reser = 1;
        } else {
            for (int i = 1; i < strlen(str); ++i) {
                if (!isdigit(str[i]) && !ischar(str[i]) && str[i] != '_') {
                    puts("Compile Error");
                    exit(0);
                }
            }
            is_var = 1;
        }
    } else if (isoperator(str)) {
        is_op = 1;
    } else {
        log("");
        puts("Compile Error");
        exit(0);
    }
    if (is_dig) {
        strcat(ans, "integer ");
    } else if (is_float) {
        strcat(ans, "float ");
    } else if (is_op) {
        strcat(ans, "operator ");
    } else if (is_reser) {
        strcat(ans, "reserved ");
    } else if (is_var) {
        strcat(ans, "variable ");
    }
}

char last;

int main() {
    s = malloc(sizeof(char) * 5005);
    while (scanf("%s", s) != EOF) { 
        last = s[strlen(s) - 1];
        for (char *pos = strchr(s, ';'); pos; s = pos + 1, pos = strchr(s, ';')) { 
            // printf("pos = %d\n", pos - s);
            *pos = 0;
            process(s);
            strcat(ans, "\n");
        }
        process(s);
    }
    // end with ';'
    if (last != ';') {
        puts("Compile Error");
        return 0;
    }
    printf(ans);
    return 0;
}