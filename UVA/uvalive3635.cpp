#include <stdio.h>
#include <string.h>
#include <math.h>
const int N = 10005;
const double pi = 4 * atan(1.0);

int n, m;
double L, R, mid, r[N];

bool judge (double cur) {
    int cnt = n;
    double now;
    for (int i = 0; i < m; i++) {
  now = r[i];
  while (now - cur > 0) {
      now -= cur;
      cnt--;
  }
  if (cnt <= 0) return true;
    }
    return false;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
  // Init;
  R = 0, L = N * N;
  memset(r, 0, sizeof(r));

  // Read;
  scanf("%d%d", &m, &n);
  for (int i = 0; i < m; i++) {
      scanf("%lf", &r[i]);
      r[i] = r[i] * r[i];
      R += r[i];
      if (L > r[i])
    L = r[i];
  }

  // Handle;
  n++;
  L /= n;
  while (fabs(R - L) >= 1e-4) {
      mid = (R + L) / 2;
      if (judge(mid))
    L = mid;
      else 
    R = mid;
  }
  printf("%.4lf\n", mid * pi);
    }
    return 0;
}
