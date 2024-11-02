#include <stdio.h>
#include <string.h>

char s[1005];
int n;

int main() {
    scanf("%d %s", &n, s);
    int len = strlen(s);
    while (n--) {
        char tmp[1005]; // remember to set a copy
        strcpy(tmp, s);
        for (int pos = 0; pos < len; ++pos) {

            int numa = 0, numb = 0;
            int exista = 0, existb = 0;
            for (int i = 1; i <= 3; ++i) {
                if (pos - i >= 0) {    // 分开考虑坐标，否则会很搞
                    if (s[pos - i] == 'A')
                        ++numa, exista = 1;
                    else if (s[pos - i] == 'B')
                        ++numb, existb = 1;
                }
                if (pos + i < len) {
                    if (s[pos + i] == 'A')
                        ++numa, exista = 1;
                    else if (s[pos + i] == 'B')
                        ++numb, existb = 1;
                }
            }



            if (s[pos] == '.') {
                if (exista + existb != 2) {
                    if (exista) {
                        if (2 <= numa && numa <= 4) {
                            tmp[pos] = 'A';
                        }
                    }
                    if (existb) {
                        if (2 <= numb && numb <= 4) {
                            tmp[pos] = 'B';
                        }
                    }
                }
            } else if (s[pos] == 'A') {
                if (numb != 0)
                    tmp[pos] = '.';
                if (numa >= 5)
                    tmp[pos] = '.';
                if (numa <= 1)
                    tmp[pos] = '.';
            } else if (s[pos] == 'B') {
                if (numa != 0)
                    tmp[pos] = '.';
                if (numb >= 5)
                    tmp[pos] = '.';
                if (numb <= 1)
                    tmp[pos] = '.';
            }
        }
        strcpy(s, tmp); // 拷回来
    }

    printf("%s\n", s);
    return 0;
}