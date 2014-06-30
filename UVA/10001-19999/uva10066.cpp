#include <stdio.h>
#include <string.h>
const int N = 1005;
int max(const int& a, const int& b) { return a > b ? a : b; }

int n, m, dp[N][N], a[N], b[N];

int main() {
    int cas = 1;
    while (scanf("%d%d", &n, &m), n + m) {
  for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
  for (int i = 1; i <= m; i++)
      scanf("%d", &b[i]);

  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
    if (a[i] == b[j])
        dp[i][j] = dp[i - 1][j - 1] + 1;
    else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
  printf("Twin Towers #%d\n", cas++);
  printf("Number of Tiles : %d\n\n", dp[n][m]);
    }
    return 0;
}
