#include <stdio.h>
#include <string.h>
const int N = 10005;
int min(int p, int q) { return p > q ? q : p; }

int n, num[N], rec[N], a[N], b[N], dp[N];

void Init() {
    memset(num, 0, sizeof(num));
    for (int i = 0; i < n; i++)
  scanf("%d", &num[i]);
    for (int i = 0; i < n; i++)
  rec[i] = num[n - i - 1];
}

void solve(int tmp[], int cnt[]) {
    memset(cnt, 0, sizeof(cnt));
    memset(dp, 0, sizeof(dp));

    int m = 0;
    for (int i = 0; i < n; i++) {
  int flag = 0;
  for (int j = 0; j < m; j++)
      if (dp[j] >= tmp[i]) {
    flag = 1;
    dp[j] = tmp[i];
    cnt[i] = j + 1;
    break;
      }

  if (!flag) {
      dp[m] = tmp[i];
      cnt[i] = ++m;
  }
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
  Init();
  solve(num, a);
  solve(rec, b);

  int Max = 0, t;
  for (int i = 0; i < n; i++) {
      t = min(a[i], b[n - i - 1]);
      if (t > Max)    Max = t;
  }
  printf("%d\n", Max * 2 - 1);
    }
    return 0;
}
