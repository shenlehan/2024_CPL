#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *rule, *command, ch;
int arg[150];
char argm[1005];
int lenr, lenc;
char out[2005];
int cnt = 0;
int tot[150];

void explain() {
    int pr = 0;
    while (pr < lenr) {
        if (rule[pr] == ':') {
            arg[rule[pr - 1]] = 1; // need argument
            // printf("pr = %d, %c is changed!\n",pr, rule[pr - 1]);
        } else {
            arg[rule[pr]] = 2; // don't need argument
            // printf("pr = %d, %c is changed!\n", pr,rule[pr - 1]);
        }
        ++pr;
    }
}

int main() {
    rule = calloc(1, sizeof(char) * 130);
    command = calloc(1, sizeof(char) * 1200);
    
    while ((ch = getchar()) != '\n' && ch != EOF)
        rule[lenr++] = ch;
    rule[lenr] = '\0';
    // printf("lenr = %d\n", lenr);

    while ((ch = getchar()) != '\n' && ch != EOF)
        command[lenc++] = ch;
    command[lenc] = '\0';
    
    explain();

  //  printf("arg[t]:%d\n", arg['t']);

    int pc = 0;
    while (command[pc] != ' ') {
        putchar(command[pc]);
        ++pc;
    }
    // puts("");

    while (pc < lenc) {
        while (command[pc] != '-' && pc < lenc) {
            ++pc;
        }
        if (pc >= lenc) break;

        ++pc;
        if (!arg[command[pc]] && command[pc - 1] == '-') {
            printf(": invalid option -- '%c'", command[pc]);
            return 0;
        } else if (arg[command[pc]] == 1) {
            pc += 2;
            if (pc >= lenc || !command[pc]) {
                printf(": option requires an argument -- '%c'", command[pc - 2]);
                return 0;
            }
        } else if (arg[command[pc]] == 2) {
            continue;
        }
    }

    pc = 0;
    puts("");
    while (command[pc] != ' ') {
        ++pc;
    }

    while (pc < lenc) {
        while (command[pc] != '-' && pc < lenc) {
            ++pc;
        }
        if (pc >= lenc) break;
        ++pc;
        out[cnt++] = command[pc];
        // printf("out[%d] = %c\n", cnt - 1, out[cnt - 1])

        if (arg[command[pc]] == 1) {
            pc += 2;
            int k = 0;
            char tmp = command[pc - 2];
            while (pc < lenc && command[pc] != ' ' && command[pc] != 0) {
                argm[k++] = command[pc++];
            }
            argm[k] = '\0';
            // printf("ADD argu[%c]: %s\n", tmp, dic[tmp]);
            printf("%c=%s\n", tmp, argm); 
        } else if (arg[command[pc]] == 2) {
            printf("%c\n", command[pc]);
            continue;
        }
    }

    return 0;
}