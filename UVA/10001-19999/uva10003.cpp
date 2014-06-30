#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 55;
int l, n, val[N], dp[N][N];

int count(int a, int b) {
    if (dp[a][b])   return dp[a][b];
    if (a == b - 1) return 0;
    dp[a][b] = 1 << 30;
    for (int i = a + 1; i < b; i++)
  if (count(a, i) + count(i, b) < dp[a][b])
      dp[a][b] = dp[a][i] + dp[i][b];
    return dp[a][b] += val[b] - val[a]; 
}

int main() {
    while (scanf("%d", &l), l) {
  scanf("%d", &n);
  memset(val, 0, sizeof(val));
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; i++)
      scanf("%d", &val[i]);
  sort(val, val + n + 1);
  val[n + 1] = l;

  printf("The minimum cutting is %d.\n", count(0, n + 1));
    }
    return 0;
}
