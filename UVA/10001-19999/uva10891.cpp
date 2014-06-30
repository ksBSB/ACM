#include <stdio.h>
#include <string.h>
const int N = 105;
const int MAX = -0x3f3f3f3f;
int n, num[N], sum[N], dpx[N][N], dpy[N][N], vis[N][N];

void search(int a, int b, int& x, int& y, int flag) {
    int &A = dpx[a][b], &B = dpy[a][b];
    if (a + 1 == b)
  A = num[b], B = 0;

    if (!vis[a][b]) {
  int s, f;
  A = sum[b] - sum[a], B = 0;
  for (int i = a + 1; i < b; i++) {
      search(i, b, s, f, !flag);
      if (flag && f + sum[i] - sum[a] > A)
    A = f + sum[i] - sum[a], B = s;
      else if (!flag && s + sum[i] - sum[a] > A)
    A = s + sum[i] - sum[a], B = f;

      search(a, i, s, f, !flag);
      if (flag && f + sum[b] - sum[i] > A)
    A = f + sum[b] - sum[i], B = s;
      else if (!flag && s + sum[b] - sum[i] > A)
    A = s + sum[b] - sum[i], B = f;
  }
    }
    vis[a][b] = 1;

    if (flag)
  x = B, y = A;
    else
  x = A, y = B;
}

void solve() {
    int s, f;

    memset(dpx, MAX, sizeof(dpx));
    memset(dpy, MAX, sizeof(dpy));
    memset(vis, 0, sizeof(vis));

    search(0, n, s, f, 0);
    printf("%d\n", s - f);
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
  // Read;
  memset(num, 0, sizeof(num));
  memset(sum, 0, sizeof(sum));
  for (int i = 1; i <= n; i++) {
      scanf("%d", &num[i]);
      sum[i] = sum[i - 1] + num[i];
  }

  solve();
    }
    return 0;
}
