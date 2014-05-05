#include <stdio.h>
#include <string.h>
const int N = 200;
const int Min = -2147483645;

int n, Max, num[N][N], sum[N];

void input() {
    Max = Min;
    memset(num, 0, sizeof(num));

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
  for (int j = 0; j < n; j++) {
      scanf("%d", &num[i][j]);
      num[i + n][j + n] = num[i + n][j] = num[i][j + n] = num[i][j];
  }
}

int solve() {
    for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
      memset(sum, 0, sizeof(sum));
      for (int k = i; k < n + i; k++) {
    int now = 0;
    for (int t = j; t < n + j; t++) {
        sum[t] += num[k][t];
        now +=sum[t];
        if (Max < now)
      Max = now;
    }
      }
  }
    }
    return Max;
}
int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  input();
  printf("%d\n", solve());
    }
    return 0;
}
