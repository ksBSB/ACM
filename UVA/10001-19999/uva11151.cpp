#include <stdio.h>
#include <string.h>
const int N = 1005;
int max(int a, int b) { return a > b ? a : b; }

char a[N], b[N];
int dp[N][N], len;

int solve() {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= len; i++) {
  for (int j = 1; j <= len; j++) {
      if (a[i - 1] == b[j - 1])
    dp[i][j] = dp[i - 1][j - 1] + 1;
      else
    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
  }
    }
    return dp[len][len];
}

int main() {
    int cas;
    scanf("%d%*c", &cas);
    while (cas--) {
  gets(a);
  len = strlen(a);
  for (int i = 0; i < len; i++)
      b[len - i - 1] = a[i];
  printf("%d\n", solve());
    }
}
