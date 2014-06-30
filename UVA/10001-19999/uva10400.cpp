#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int N = 105;
const int M = 32000;
const char sign[] = "+-*/";
int n, num[N], order, vis[N][2 * M + 10];
char str[N];

int count(int sum, char c, int number) {
    if (c == '+')
  return sum + number;
    else if (c == '-')
  return sum - number;
    else if (c == '*')
  return sum * number;
    else if (c == '/')
  return sum / number; 
    return 0;
}

int find(int sum, int deep) {
    if (deep == n) {
  if (sum == order) {
      str[deep - 1] = '=';
      return true;
  }
  else
      return false;
    }
    int cur;
    for (int i = 0; i < 4; i++) {
  if (i == 3 && (num[deep] == 0))  continue;
  cur = count(sum, sign[i], num[deep]); 
  if (cur < -32000 || cur > 32000)  continue;
  if (vis[deep][cur + M])   continue;

  if (find(cur, deep + 1)) {
      str[deep - 1] = sign[i];
      return true;
  }
  vis[deep][cur + M] = 1;
    }
    return false;
}

int main () {
    int cas, flag;
    scanf("%d", &cas);
    while (cas--) {
  memset(str, 0, sizeof(str));
  memset(vis, 0, sizeof(vis));

  scanf("%d", &n);
  for (int i = 0; i < n; i++)
      scanf("%d", &num[i]);
  scanf("%d", &order);

  if (find(num[0], 1)) {
      for (int i = 0; i < n; i++)
    printf("%d%c", num[i], str[i]);
      printf("%d\n", order);
  }
  else
      printf("NO EXPRESSION\n");
    }
    return 0;
}
