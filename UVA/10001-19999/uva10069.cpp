#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
const int N = 10005;
const int M = 105;

struct bign {
    int len, sex;
    int s[M];

    bign() {
  this -> len = 1;
  this -> sex = 0;
  memset(s, 0, sizeof(s));
    }

    bign operator = (const char *number) {
  int begin = 0;
  len = 0;
  sex = 1;
  if (number[begin] == '-') {
      sex = -1;
      begin++;
  }
  else if (number[begin] == '+')
      begin++;

  for (int j = begin; number[j]; j++)
      s[len++] = number[j] - '0';
    }

    bign operator = (int number) {
  char string[N];
  sprintf(string, "%d", number);
  *this = string;
  return *this;
    }

    bign (int number) {*this = number;}
    bign (const char* number) {*this = number;}

    bign change(bign cur) {
  bign now;
  now = cur;
  for (int i = 0; i < cur.len; i++)
      now.s[i] = cur.s[cur.len - i - 1];
  return now;
    }

    void delZore() {  // 删除前导0.
  bign now = change(*this);
  while (now.s[now.len - 1] == 0 && now.len > 1) {
      now.len--;
  }
  *this = change(now);
    }

    void put() {    // 输出数值。
  delZore();
  if (sex < 0 && (len != 1 || s[0] != 0))
      cout << "-";
  for (int i = 0; i < len; i++)
      cout << s[i];
    }

    bign operator + (const bign &cur){  
  bign sum, a, b;  
  sum.len = 0;
  a = a.change(*this);
  b = b.change(cur);

  for (int i = 0, g = 0; g || i < a.len || i < b.len; i++){  
      int x = g;  
      if (i < a.len) x += a.s[i];  
      if (i < b.len) x += b.s[i];  
      sum.s[sum.len++] = x % 10;  
      g = x / 10;  
  }  
  return sum.change(sum);  
    } 
};

bign cnt[M][N], sum;
char x[N], z[M];

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  scanf("%s%s", x, z);
  int n = strlen(x), m = strlen(z);
  for (int i = 0; i <= n; i++)
      cnt[0][i] = 1;

  for (int i = 1; i <= m; i++) {
      cnt[i][0] = 0;
      for (int j = 1; j <= n; j++) {
    cnt[i][j] = cnt[i][j - 1];
    if (z[i - 1] == x[j - 1])   
        cnt[i][j] = cnt[i][j] + cnt[i - 1][j - 1];
      }
  }
  cnt[m][n].put();
  printf("\n");
    }
    return 0;
}
