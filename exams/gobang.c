#include <stdio.h>

int T;
char map[30][30];

int in(int x, int y) {
    return 0 <= x && x < 20 && 0 <= y && y < 20;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 20; ++i) {
            scanf("%s", map[i]);
        }

        // find ****_ or ***** missing one
        // then white win
        int cnt1 = 0, cnt5 = 0;
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                if (map[i][j] == '*') {
                    int ok = 1;
                    for (int k = 1; k <= 3; ++k) {
                        if (in(i, j + k) && map[i][j + k] == '*') continue;
                        else {
                            ok = 0;
                            break;
                        }
                    }
                    if (!((in(i, j - 1) && map[i][j - 1] == '_') || (in(i, j + 4) && map[i][j + 4] == '_'))) ok = 0;
                    cnt1 += ok;

                    ok = 1;
                    for (int k = 1; k <= 3; ++k) {
                        if (in(i + k, j + k) && map[i + k][j + k] == '*') continue;
                        else {
                            ok = 0;
                            break;
                        }
                    }
                    if (!((in(i - 1, j - 1) && map[i - 1][j - 1] == '_') || (in(i + 4, j + 4) && map[i + 4][j + 4] == '_'))) ok = 0;
                    cnt1 += ok;

                    ok = 1;
                    for (int k = 1; k <= 3; ++k) {
                        if (in(i + k, j - k) && map[i + k][j - k] == '*') continue;
                        else {
                            ok = 0;
                            break;
                        }
                    }
                    if (!((in(i - 1, j + 1) && map[i - 1][j + 1] == '_') || (in(i + 4, j - 4) && map[i + 4][j - 4] == '_'))) ok = 0;
                    cnt1 += ok;

                    ok = 1;
                    for (int k = 1; k <= 3; ++k) {
                        if (in(i + k, j) && map[i + k][j] == '*') continue;
                        else {
                            ok = 0;
                            break;
                        }
                    }
                    if (!((in(i - 1, j) && map[i - 1][j] == '_') || (in(i + 4, j) && map[i + 4][j] == '_'))) ok = 0;
                    cnt1 += ok;

                    int tot1 = 0, tot2 = 0; // tot1 is *, tot2 is _
                    for (int k = 1; k <= 4; ++k) {
                        if (in(i, j + k)) {
                            if (map[i][j + k] == '*') ++tot1;
                            else if (map[i][j + k] == '_') ++tot2;
                        }
                    }
                    if (tot1 == 3 && tot2 == 1) {
                        ++cnt5;
                    }

                    tot1 = tot2 = 0;
                    for (int k = 1; k <= 4; ++k) {
                        if (in(i + k, j + k)) {
                            if (map[i + k][j + k] == '*') ++tot1;
                            else if (map[i + k][j + k] == '_') ++tot2;
                        }
                    }
                    if (tot1 == 3 && tot2 == 1) {
                        ++cnt5;
                    }

                    tot1 = tot2 = 0;
                    for (int k = 1; k <= 4; ++k) {
                        if (in(i + k, j - k)) {
                            if (map[i + k][j - k] == '*') ++tot1;
                            else if (map[i + k][j - k] == '_') ++tot2;
                        }
                    }
                    if (tot1 == 3 && tot2 == 1) {
                        ++cnt5;
                    }

                    tot1 = tot2 = 0;
                    for (int k = 1; k <= 4; ++k) {
                        if (in(i + k, j)) {
                            if (map[i + k][j] == '*') ++tot1;
                            else if (map[i + k][j] == '_') ++tot2;
                        }
                    }
                    if (tot1 == 3 && tot2 == 1) {
                        ++cnt5;
                    }
                }
            }
        }
        if (cnt1 >= 1 || cnt5 >= 1) {
            puts("Lose");
            continue;
        }

        // find ####_ >= 2 or _####_ >= 1 or ##### missing one
        // then black win
        int cnt2 = 0, cnt3 = 0, cnt4 = 0;
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                if (map[i][j] == '#') {
                    int ok1 = 1, ok2 = 1;
                    for (int k = 1; k <= 3; ++k) {
                        if (in(i, j + k) && map[i][j + k] == '#') continue;
                        else {
                            ok1 = ok2 = 0;
                            break;
                        }
                    }
                    if (!((in(i, j - 1) && map[i][j - 1] == '_') || (in(i, j + 4) && map[i][j + 4] == '_'))) ok1 = 0;
                    if (!((in(i, j - 1) && map[i][j - 1] == '_') && (in(i, j + 4) && map[i][j + 4] == '_'))) ok2 = 0;
                    cnt2 += ok1;
                    cnt3 += ok2;

                    ok1 = ok2 = 1;
                    for (int k = 1; k <= 3; ++k) {
                        if (in(i + k, j + k) && map[i + k][j + k] == '#') continue;
                        else {
                            ok1 = ok2 = 0;
                            break;
                        }
                    }
                    if (!((in(i - 1, j - 1) && map[i - 1][j - 1] == '_') || (in(i + 4, j + 4) && map[i + 4][j + 4] == '_'))) ok1 = 0;
                    if (!((in(i - 1, j - 1) && map[i - 1][j - 1] == '_') && (in(i + 4, j + 4) && map[i + 4][j + 4] == '_'))) ok2 = 0;
                    cnt2 += ok1;
                    cnt3 += ok2;

                    ok1 = ok2 = 1;
                    for (int k = 1; k <= 3; ++k) {
                        if (in(i + k, j - k) && map[i + k][j - k] == '#') continue;
                        else {
                            ok1 = ok2 = 0;
                            break;
                        }
                    }
                    if (!((in(i - 1, j + 1) && map[i - 1][j + 1] == '_') || (in(i + 4, j - 4) && map[i + 4][j - 4] == '_'))) ok1 = 0;
                    if (!((in(i - 1, j + 1) && map[i - 1][j + 1] == '_') && (in(i + 4, j - 4) && map[i + 4][j - 4] == '_'))) ok2 = 0;
                    cnt2 += ok1;
                    cnt3 += ok2;

                    ok1 = ok2 = 1;
                    for (int k = 1; k <= 3; ++k) {
                        if (in(i + k, j) && map[i + k][j] == '#') continue;
                        else {
                             ok1 = ok2 = 0;
                            break;
                        }
                    }
                    if (!((in(i - 1, j) && map[i - 1][j] == '_') || (in(i + 4, j) && map[i + 4][j] == '_'))) ok1 = 0;
                    if (!((in(i - 1, j) && map[i - 1][j] == '_') && (in(i + 4, j) && map[i + 4][j] == '_'))) ok2 = 0;
                    cnt2 += ok1;
                    cnt3 += ok2;

                    int tot1 = 0, tot2 = 0; // tot1 is #, tot2 is _
                    for (int k = 1; k <= 4; ++k) {
                        if (in(i, j + k)) {
                            if (map[i][j + k] == '#') ++tot1;
                            else if (map[i][j + k] == '_') ++tot2;
                        }
                    }
                    if (tot1 == 3 && tot2 == 1) {
                        ++cnt4;
                    }

                    tot1 = tot2 = 0;
                    for (int k = 1; k <= 4; ++k) {
                        if (in(i + k, j + k)) {
                            if (map[i + k][j + k] == '#') ++tot1;
                            else if (map[i + k][j + k] == '_') ++tot2;
                        }
                    }
                    if (tot1 == 3 && tot2 == 1) {
                        ++cnt4;
                    }

                    tot1 = tot2 = 0;
                    for (int k = 1; k <= 4; ++k) {
                        if (in(i + k, j - k)) {
                            if (map[i + k][j - k] == '#') ++tot1;
                            else if (map[i + k][j - k] == '_') ++tot2;
                        }
                    }
                    if (tot1 == 3 && tot2 == 1) {
                        ++cnt4;
                    }

                    tot1 = tot2 = 0;
                    for (int k = 1; k <= 4; ++k) {
                        if (in(i + k, j)) {
                            if (map[i + k][j] == '#') ++tot1;
                            else if (map[i + k][j] == '_') ++tot2;
                        }
                    }
                    if (tot1 == 3 && tot2 == 1) {
                        ++cnt4;
                    }

                }
            }
        }
        if (cnt2 >= 2 || cnt3 >= 1 || cnt4 >= 2) {
            puts("Win");
            continue;
        }        

        // not sure
        puts("Not Sure");
    }
    return 0;
}