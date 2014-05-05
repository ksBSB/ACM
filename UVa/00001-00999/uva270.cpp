#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int max(const int &a, const int &b) { return a > b ? a : b;}
const int N = 1005;

int n, x[N], y[N];

int find (int p, int q, int c) {
    int cnt = 0;
    for (int i = c + 1; i < n; i++) {
  if (p * (y[i] - y[c]) == q * (x[i] - x[c]))
    cnt++;
    }
    return cnt;
}

int solve() {
    int Max = 1;
    for (int i = 0; i < n; i++) {
  for (int j = i + 1; j < n; j++) {
      int cur = find(x[j] - x[i], y[j] - y[i], j) + 2;
      Max = max(Max, cur);
  }
    }
    return Max;
}

int main() {
    int cas;
    char str[N];
    scanf("%d%*c%*c", &cas);
    while (cas--) {
  // Init;
  memset(x, 0, sizeof(x));
  memset(y, 0, sizeof(y));
  n = 0;
  
  // Read;
  while (gets(str)) {
      if (!str[0] && n) break;
      sscanf(str, "%d%d", &x[n], &y[n]);
      n++;
  }

  printf("%d\n", solve());
  if (cas)    printf("\n");
    }
    return 0;
}
