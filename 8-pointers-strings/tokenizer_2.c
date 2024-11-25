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

char sen[5005][5005], ch, prev;
char ans[5000005];
char tmp[5000005];
int word_cnt[5005];
int sent_cnt, len;
int sep_cnt = 0;

int main() {
    while ((ch = getchar())) {
        if (ch == EOF) {
            if (prev != ';') {
                log("");
                puts("Compile Error");
                return 0;
            }
            break;
        }
        if (ch == '\n') {
            // prev = ch;
            sen[sent_cnt][len++] = ' ';
            continue;
        }
        if (ch == ';') {
            prev = ';';
            ++sep_cnt;
            sen[sent_cnt][len] = '\0';
            ++sent_cnt;
            len = 0;
            continue;
        }

        if (ch != ' ')
            prev = ch;
        sen[sent_cnt][len++] = ch;
    }

    // for (int i = 0; i < sent_cnt; ++i) {
    //     puts(sen[i]);
    // }
    // printf("sep_cnt = %d, sent_cnt = %d\n", sep_cnt, sent_cnt);

    for (int s = 0; s < sent_cnt; ++s) {
        int ps = 0;
        log("Now senlen = %d", strlen(sen[s]));
        while (ps < strlen(sen[s])) {
            while (sen[s][ps] == ' ' && ps < strlen(sen[s])) {
                ++ps;
            }

            // get word
            int t = 0;
            for (int k = ps; k < strlen(sen[s]) && sen[s][k] != ' ' && sen[s][k] != '\0'; ++k) {
                tmp[t++] = sen[s][k];
            }
            tmp[t] = '\0';
            log("Now word:%s##ps=%d", tmp, ps);
            if (strlen(tmp) == 0) {
                continue;
            }

            // process word
            int is_dig = 0, is_float = 0, is_var = 0, is_op = 0, is_reser = 0;
            if (isdigit(sen[s][ps])) {
                is_dig = 1;
                int dot = 0;
                for (int k = ps; k < strlen(sen[s]) && sen[s][k] != ' ' && sen[s][k] != '\0'; ++k) {
                    if (sen[s][k] == '.') {
                        is_float = 1;
                        is_dig = 0;
                        ++dot;
                    }
                    if (!isdigit(sen[s][k]) && sen[s][k] != '.') {
                        puts("Compile Error");
                        log("");
                        return 0;
                    }
                    if (dot >= 2) {
                        log("");
                        puts("Compile Error");
                        return 0;                        
                    }
                }
            } else if (sen[s][ps] == '.') {
                int dot = 0;
                for (int k = ps; k < strlen(sen[s]) && sen[s][k] != ' ' && sen[s][k] != '\0'; ++k) {
                    if (sen[s][k] == '.') {
                        is_float = 1;
                        ++dot;
                    }
                    if (!isdigit(sen[s][k]) && sen[s][k] != '.') {
                        puts("Compile Error");
                        log("");
                        return 0;
                    }
                    if (dot >= 2) {
                        log("");
                        puts("Compile Error");
                        return 0;                        
                    } 
                }
                if (strlen(tmp) == 1) {
                    puts("Compile Error");
                    return 0;
                }            
            } else if (ischar(sen[s][ps]) || sen[s][ps] == '_') {
                if (isreserved(tmp)) {
                    is_reser = 1;
                } else {
                    for (int i = 1; i < strlen(tmp); ++i) {
                        if (!isdigit(tmp[i]) && !ischar(tmp[i]) && tmp[i] != '_') {
                            puts("Compile Error");
                            return 0;
                        }
                    }
                    is_var = 1;
                }
            } else if (isoperator(tmp)) {
                is_op = 1;
            } else {
                log("");
                puts("Compile Error");
                return 0;
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

            ps += strlen(tmp);
        }
        strcat(ans, "\n");
    }
    printf(ans);
    return 0;
}