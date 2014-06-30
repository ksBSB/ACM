#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int M = 25;

struct State {
    char name[M];
    int money;
    int wei;
}s[N][N];
int cnt, sum, son[N];
char str[N][M], sex[M];

bool cmp(const State& a, const State& b) {
    return a.money < b.money;
}

int find(char sex[]) {
    for (int i = 0; i < cnt; i++)
  if(strcmp(sex, str[i]) == 0)
      return i;
    strcpy(str[cnt], sex);
    return cnt;
}

bool judge(int Min) {
    int tmp = 0;
    for (int i = 0; i < cnt; i++) {
  int flag = 1;
  for (int j = 0; j < son[i]; j++) {
      if (s[i][j].wei >= Min) {
    flag = 0;
    tmp += s[i][j].money;
    break;
      }
  }
  if (flag || tmp > sum)  return false;
    }
    return true;
}

int main() {
    State now;
    int cas, n, cur, L, R;
    scanf("%d", &cas);
    while (cas--) {
  memset(s, 0, sizeof(s));
  memset(son, 0, sizeof(son));
  memset(str, 0, sizeof(str));
  cnt = L = R = 0;

  scanf("%d%d", &n, &sum);
  for (int i = 0; i < n; i++) {
      scanf("%s%s%d%d", sex, now.name, &now.money, &now.wei);
      if (now.wei > R)  R = now.wei;
      cur = find(sex);
      s[cur][son[cur]++] = now;
      if (cur == cnt) cnt++;
  }


  for (int i = 0; i < cnt; i++)
      sort(s[i], s[i] + son[i], cmp);

  int mid;
  while (L < R) {
      mid = (L + R) / 2;
      if (L == mid)   break;
      if (judge(mid))
    L = mid;
      else
    R = mid;
  }
  if (judge(mid + 1)) mid++;
  printf("%d\n", mid);
    }
    return 0;
}
