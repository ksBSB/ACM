#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int N = 305;

long long dp[N][N];

void Init() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= 300; i++) {
  for (int j = i; j <= 300; j++) {
      for (int k = 1; k <= 300; k++)
    dp[j][k] += dp[j - i][k - 1];
  } 
    }
}

int main() {
    Init();
    int n, a, b;
    char str[N];
    while (gets(str)) {
  int flag = sscanf(str, "%d%d%d", &n, &a, &b);
  long long sum = 0;
  if (a > 300)  a = 300;
  if (b > 300)  b = 300;
  if (flag == 1) {
      for (int i = 0; i <= n; i++)
    sum += dp[n][i];
  }
  else if (flag == 2) {
      for (int i = 0; i <= a; i++)
    sum += dp[n][i];
  }
  else if (flag == 3) {
      for (int i = a; i <= b; i++)
    sum += dp[n][i];
  }
  printf("%lld\n", sum);
    }
    return 0;
}
