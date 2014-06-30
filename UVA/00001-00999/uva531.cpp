#include <stdio.h>
#include <string.h>
const int N = 105;
const int M = 30;
int max(int a, int b) { return a > b ? a : b; }

int n, m, ans[N], dp[N][N], x[N][N], y[N][N];
char a[N][M], b[N][M];

void Init() {
    n = m = 0;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(x, -1, sizeof(x));
    memset(y, -1, sizeof(y));
    memset(dp, 0, sizeof(dp));
}

int read() {
    int flag = 0;
    while (1) {
  if (scanf("%s", a[n]) != 1) {
      flag = 1;
      break;
  }
  if (strcmp(a[n], "#") == 0) break;
  n++;
    }

    while (1) {
  if (scanf("%s", b[m]) != 1) {
      flag = 1;
      break;
  }
  if (strcmp(b[m], "#") == 0) break;
  m++;
    }
    return flag;
}

void solve() {
    memset(ans, -1, sizeof(ans));
    for (int i = 1; i <= n; i++) {
  for (int j = 1; j <= m; j++) {
      if (strcmp(a[i - 1], b[j - 1]) == 0) {
    dp[i][j] = dp[i - 1][j - 1] + 1;
    x[i][j] = i - 1;
    y[i][j] = j - 1;
      }
      else {
    if (dp[i - 1][j] > dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j];
        x[i][j] = i - 1;
        y[i][j] = j;
    }
    else {
        dp[i][j] = dp[i][j - 1];
        x[i][j] = i;
        y[i][j] = j - 1;
    }
      }
  }
    }

    int sum = dp[n][m] - 1, p = n, q = m;

    while (1) {
  if (x[p][q] == -1 || y[p][q] == -1) break;
  if (sum < 0)  break;
  if ((p == x[p][q] + 1) && (q == y[p][q] + 1)) {
      ans[sum--] = x[p][q];
  }
  int t = p;
  p = x[t][q], q = y[t][q];
    }
}

int main() {
    while (1) {
  Init();
  if (read()) break;
  solve();

  if (dp[n][m]) {
      for (int i = 0; i < dp[n][m] - 1; i++)
    printf("%s ", a[ans[i]]); 
      printf("%s\n", a[ans[dp[n][m] - 1]]);
  }
    }
    return 0;
}
