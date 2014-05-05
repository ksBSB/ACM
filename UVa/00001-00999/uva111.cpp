#include <stdio.h>
#include <string.h>
const int N = 1005;
int max (const int &x, const int& y) { return x > y ? x : y; }

int a[N], b[N], dp[N][N];
int main() {
    int n, t;
    while (scanf("%d", &n) == 1) {
  for (int i = 1; i <= n; i++) {
      scanf("%d", &t);
      a[t] = i;
  }

  while (scanf("%d", &t) == 1) {
      b[t] = 1;

      for (int i = 2; i <= n; i++) {
    scanf("%d", &t);
    b[t] = i;
      }

      memset(dp, 0, sizeof(dp));
      for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        if (a[i] != b[j])
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        else
      dp[i][j] = dp[i - 1][j - 1] + 1;
    }

      printf("%d\n", dp[n][n]);
  }
    }
    return 0;
}
