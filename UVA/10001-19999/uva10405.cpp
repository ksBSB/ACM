#include <stdio.h>
#include <string.h>
const int N = 1005;
int max(const int& a, const int& b) { return a > b ? a : b; }

char a[N], b[N];
int n, m, dp[N][N];

int main() {
    while (gets(a)) {
  gets(b);
  n = strlen(a);
  m = strlen(b);
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
    if (a[i - 1] == b[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
    else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
  printf("%d\n", dp[n][m]);
    }
    return 0;
}
