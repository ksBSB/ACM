#include <stdio.h>
#include <string.h>
const int N = 1005;
const int M = 10;
const char sign[M][10]= {"front", "back", "left", "right", "top", "bottom"};

struct state {
    int in;
    int out;
}tmp[N][M];
int n, x[N][M], y[N][M], dp[N][M];

void Init() {
    memset(tmp, 0, sizeof(tmp));
    memset(dp, 0, sizeof(dp));
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
}

void write(int k, int a, int b, int d) {
    tmp[d][k].in = a;
    tmp[d][k].out = b;
}

void read() {
    int a, b;
    for (int i = 1; i <= n; i++) {
  for (int j = 0; j < 3; j++) {
      scanf("%d%d", &a, &b);
      write(j * 2, a, b, i);
      write(j * 2 + 1, b, a, i);
  }
    }
}

int search(int d, int k) {
    if (dp[d][k]) return dp[d][k];

    for (int i = d + 1; i <= n; i++) {
  for (int j = 0; j < 6; j++) {
      if (tmp[i][j].in == tmp[d][k].out) {
    int a = search(i, j);
    if (a > dp[d][k]) {
        dp[d][k] = a;
        x[d][k] = i, y[d][k] = j;
    }
      }
  }
    }
    return ++dp[d][k];
}

void solve() {
    int Max = 0, idx, idy, a;
    for (int i = 1; i <= n; i++) {
  
  if (Max + i >= n)   break;

  for (int j = 0; j < 6; j++) {
      a = search(i, j);
      if (a > Max) {
    Max = a;
    idx = i, idy = j;
      }
  }
    }
    printf("%d\n", Max);

    for (int i = 0; i < Max; i++) {
  printf("%d %s\n", idx, sign[idy]);
  a = idx;
  idx = x[idx][idy];
  idy = y[a][idy];
    }

    /*
    printf("%d\n", dp[1][5]);
    idx = 1; idy = 5;
    for (int i = 0; idx; i++) {
  printf("%d %s\n", idx, sign[idy]);
  a = idx;
  idx = x[idx][idy];
  idy = y[a][idy];
    }
    */
}

int main() {
    int cas = 0;
    while (scanf("%d", &n), n) {
  Init();

  read();

  if (cas)    printf("\n");

  printf("Case #%d\n", ++cas);

  solve();
    }
    return 0;
}
