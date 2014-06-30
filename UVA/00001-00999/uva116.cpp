#include <stdio.h>
#include <string.h>
const int N = 105;
int min (int a, int b) {    return a < b ? a : b; }

int n, m, sum, ans[N], num[N][N], rec[N][N];

void solve() {
    int k, t, a, i, c;
    memset(rec, -1, sizeof(rec));
    for (int j = m - 1; j > 0; j--) {
  k = j + 1;
  for (int i = 1; i <= n; i++) {
      a = i - 1;
      if (a == 0) a = n;
      c = i + 1;
      if (c == n + 1) c = 1;
      if (num[a][k] <= num[i][k] && num[a][k] <= num[c][k]) {
    num[i][j] += num[a][k];
    t = a;
    if (num[a][k] == num[i][k]) t = min(t, i);
    if (num[a][k] == num[c][k]) t = min(t, c);
    rec[i][j] = t;
      }
      else if (num[i][k] <= num[a][k] && num[i][k] <= num[c][k]) {
    num[i][j] += num[i][k];
    t = i;
    if (num[i][k] == num[a][k]) t = min(t, a);
    if (num[i][k] == num[c][k]) t = min(t, c);
    rec[i][j] = t;
      }
      else {
    num[i][j] += num[c][k];
    t = c;
    if (num[c][k] == num[a][k]) t = min(t, a);
    if (num[c][k] == num[i][k]) t = min(t, i);
    rec[i][j] = t;
      }
  }
    }

    sum = 1 << 30, t = 0;
    for (int i = 1; i <= n; i++) {
  if (num[i][1] < sum) {
      sum = num[i][1];
      t = i;
  }
    }
    
    for (int i = 1; i < m; i++) {
  ans[i] = t;
  t = rec[t][i];
    }
    ans[m] = t;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
  // Read;
  memset(num, 0, sizeof(num));
  for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++)
    scanf("%d", &num[i][j]);
  }

  solve();
  for (int i = 1; i < m; i++)
      printf("%d ", ans[i]);
  printf("%d\n%d\n", ans[m], sum);
    }
    return 0;
}
