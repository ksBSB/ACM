#include <stdio.h>
#include <string.h>
const int N = 1005;
int max(const int& x, const int& y) { return x > y ? x : y; }

int n, m, dp[N][N];
char a[N], b[N];

int main() {
    int cas = 1;
    while (gets(a)) {
  if (strcmp(a, "#") == 0)    break;
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
  printf("Case #%d: you can visit at most %d cities.\n", cas++, dp[n][m]);
    }
    return 0;
}
