#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char _0[17][9 + 1] = { // +1 for '\0'
  "..#####.",
  ".######.",
  "##....##",
  "##....##",
  "##.....#",
  "##.....#",
  "##.....#",
  "##.....#",
  "##.....#",
  "##.....#",
  "##.....#",
  "##.....#",
  "##.....#",
  "##....##",
  "##....##",
  ".######.",
  "..####.."
};

const char _1[17][9 + 1] = {
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
  "##",
};

const char _2[17][9 + 1] = {
  "..#####..",
  ".#######.",
  "##....##.",
  ".......##",
  "......##.",
  "......##.",
  "......##.",
  ".....##..",
  "....###..",
  "...###...",
  "...##....",
  "..###....",
  ".###.....",
  ".##......",
  "###......",
  "########.",
  "########."
};

const char _3[17][9 + 1] = {
  "########",
  "########",
  ".....###",
  "....###.",
  "...###..",
  "..###...",
  "..#####.",
  "..######",
  "......##",
  "......##",
  "......##",
  "......##",
  "##....##",
  "##....##",
  "###...##",
  ".######.",
  "..####.."
};

const char _4[17][9 + 1] = {
  ".....##..",
  "....###..",
  "....###..",
  "...####..",
  "...####..",
  "...####..",
  "..#####..",
  "..##.##..",
  ".###.##..",
  ".##..##..",
  ".##..##..",
  "##...##..",
  "#########",
  "#########",
  ".....##..",
  ".....##..",
  ".....##.."
};

const char _5[17][9 + 1] = {
  "########.",
  "########.",
  "##.......",
  "##.......",
  "##.......",
  "##.......",
  "#######..",
  "########.",
  "......###",
  ".......##",
  ".......##",
  ".......##",
  ".......##",
  "##.....##",
  ".##...###",
  ".#######.",
  "..#####.."
};

const char _6[17][9 + 1] = {
  ".....#...",
  "....##...",
  "...##....",
  "..###....",
  "..##.....",
  ".##......",
  ".##......",
  ".#####...",
  "#######..",
  "###...##.",
  "##....##.",
  "##.....##",
  "##.....##",
  "##.....##",
  "###...##.",
  ".#######.",
  "..####..."
};

const char _7[17][9 + 1] = {
  "#########",
  "#########",
  ".......#.",
  "......##.",
  "......##.",
  ".....##..",
  ".....##..",
  ".....#...",
  "....##...",
  "....##...",
  "....##...",
  "...##....",
  "...##....",
  "...##....",
  "...##....",
  "...##....",
  "...##....",
};

const char _8[17][9 + 1] = {
  "..#####..",
  ".##...##.",
  "##.....#.",
  "##.....#.",
  "##.....#.",
  "##....##.",
  ".##..###.",
  "..#####..",
  ".#######.",
  "##....##.",
  "##.....##",
  "##.....##",
  "##.....##",
  "##.....##",
  "###..###.",
  ".######..",
  "...###..."
};

const char _9[17][9 + 1] = {
  ".######..",
  ".##..###.",
  "##....##.",
  "##.....##",
  "##.....##",
  "##.....##",
  "##....##.",
  ".#######.",
  "..######.",
  ".....###.",
  ".....##..",
  "....###..",
  "....##...",
  "...##....",
  "..###....",
  ".###.....",
  "........."
};

struct Number {
  const char (*p)[10]; // 数字字符 (注意这里的类型，因为每个字符是一个若干行、10 列的二维数组，这里与二维数组作函数参数时的用法一致)
  int n; // 数字字符所占的行数
  int m; // 数字字符所占的列数
};

struct Number numbers[] = {
  {_0, 17, 8},
  {_1, 17, 2},
  {_2, 17, 9},
  {_3, 17, 8},
  {_4, 17, 9},
  {_5, 17, 9},
  {_6, 17, 9},
  {_7, 17, 9},
  {_8, 17, 9},
  {_9, 17, 9},
};

// 你可以通过 (numbers[k].p)[i][j] 访问 _k[i][j] 

char s[55][105];
int u = -1, l = -1;
int ans[10], tot;

int judgeLine(int i) {
    for (int j = 0; j < 100; ++j) {
        if (s[i][j] == '#') return 1;
    }
    return 0;
}

int judgeCol(int j) {
    for (int i = 0; i < 50; ++i) {
        if (s[i][j] == '#') return 1;
    }
    return 0;  
}

int judge(int left, int right) {
  // puts("~~~~~~~~~~~");
  //   for (int i = u; i <= l; ++i) {
  //     for (int j = left; j <= right; ++j) {
  //       printf("%c", s[i][j]);
  //     }
  //     puts("");
  //   }
  // puts("~~~~~~~~~~~");


  for (int k = 0; k <= 9; ++k) {
    int suc = 1;
    // modified here!
    if (numbers[k].n != l - u + 1 || numbers[k].m != right - left + 1) {
      continue;
    }
    for (int i = u; i <= l; ++i) {
      for (int j = left; j <= right; ++j) {
        if ((numbers[k].p)[i - u][j - left] != s[i][j]) {
          suc = 0;
        }
      }
    }
    if (suc) {
      return k;
    }
  }
  return -1;
}

int main() {
    for (int i = 0; i < 50; ++i) {
        scanf("%s", s[i]);
    }
    // find u and l
    for (int i = 0; i < 50; ++i) {
        if (judgeLine(i)) {
            if (u == -1) u = i;
        } else {
            if (u >= 0) {
                l = i - 1;
                break;
            }
        }
    }
    printf("%d %d\n", u, l);

    int left = -1, right = -1;
    for (int j = 99; j >= 0; --j) {
      if (right == -1 && judgeCol(j)) {
        right = j;
      } else if (!judgeCol(j)) {
        if (right >= 0) {
          left = j + 1;
          int res = judge(left, right);
          if (res != -1) ans[tot++] = res;
          left = right = -1;
        }
      }
    }
    for (int i = tot - 1; i >= 0; --i) printf("%d ", ans[i]);
    return 0;
}