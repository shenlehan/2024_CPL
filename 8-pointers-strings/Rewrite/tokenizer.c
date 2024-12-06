#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define log(f, args...) 
// do { printf("%d %s ", __LINE__, __FUNCTION__); printf(f, ##args); puts(""); } while (0)

const char *reserved[30] = {
    "const", "int", "float", "double",
    "long", "static", "void", "char",
    "extern", "return", "break", "enum",
    "struct", "typedef", "union", "goto"
};

const char *oper[11] = {
    "+", "-", "*", "/",
    ">", "<", "=", 
    "==", "!=", ">=",
    "<=", 
};

char *s, *ans;

void word(const char *str) {
    log("str = %s", str);
    if (!strlen(str)) {
        return;
    }
    for (int i = 0; i < 16; ++i) {
        if (!strcmp(str, reserved[i])) {
            strcat(ans, "reserved ");
            log("");
            return;
        }
    }
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] != '_' && !isdigit(str[i]) && !isalpha(str[i])) {
            puts("Compile Error");
            log("");
            exit(0);
        }
    }
    strcat(ans, "variable ");
}

void floatnum(const char *str) {
    log("str = %s", str);
    if (!strlen(str)) {
        return;
    }
    int dotnum = 0;
    if (!strcmp(str, ".")) {
        log("");
        puts("Compile Error");
        exit(0);
    }
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '.') {
            ++dotnum;
            if (dotnum >= 2) {
                puts("Compile Error");
                exit(0);
                log("");
            }
        } else if (!isdigit(str[i]) && str[i] != '.') {
            log("");
            puts("Compile Error");
            exit(0);            
        }
    }
    strcat(ans, "float ");
}

void integer(const char *str) {
    log("str = %s", str);
    if (!strlen(str)) {
        return;
    }
    for (int i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i])) {
            puts("Compile Error");
            // log("str = %s, str[%d] =%c###", str, i, str[i]);
            exit(0);
        }
    }
    strcat(ans, "integer ");
}

void operator(const char *str) {
    log("str = %s", str);
    if (!strlen(str)) {
        return;
    }
    if (strlen(str) == 1) {
        for (int i = 0; i < 7; ++i) {
            if (str[0] == oper[i][0]) {
                strcat(ans, "operator ");
                return;
            }
        }
        puts("Compile Error");
        exit(0); 
    } else if (strlen(str) == 2) {
        for (int i = 7; i < 11; ++i) {
            if (strcmp(str, oper[i]) == 0) {
                strcat(ans, "operator ");
                return;
            }
        }
        puts("Compile Error");
        exit(0); 
    } else {
        log("");
        puts("Compile Error");
        exit(0); 
    }
}

void process(const char *str) {
    log("str = %s", str);
    if (isalpha(str[0]) || str[0] == '_') {
        word(str);
    } else if (str[0] == '.' || strchr(str, '.') != NULL) {
        floatnum(str);
    } else if (isdigit(str[0]) && strchr(str, '.') == NULL) {
        integer(str);
    } else {
        operator(str);
    }
}

int main() {
    s = calloc(1, sizeof(char) * 4096);
    ans = calloc(1, sizeof(char) * 4096);
    
    char last;
    while (scanf("%s", s) != EOF) {
        for (char *pos = strchr(s, ';'); pos; s = pos + 1, pos = strchr(s, ';')) {
            if (strlen(s)) // remember there will always be empty string! be careful with that
                last = s[strlen(s) - 1];
            *pos = 0;
            process(s);  
            strcat(ans, "\n");
        }
        process(s); // last string before ';'
    }
    // printf("lastchar = %c\n", last);
    if (last != ';') {
        puts("Compile Error");
        return 0;
    }
    printf("%s", ans);
    return 0;
}