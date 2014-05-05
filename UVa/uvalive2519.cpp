#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
const int N = 1005;

struct thing {
    double l;
    double r;
}tmp[N];

bool cmp(const thing& a, const thing& b) {
    if (a.r != b.r) return a.r - b.r < 0;
    else    return a.l - b.l > 0;
}

int main() {
    int n, r, x, y, cas = 1;
    while (scanf("%d%d", &n, &r) == 2 && n + r) {
  // Init;
  int flag = 0;
  double t;
  memset(tmp, 0, sizeof(tmp));

  // Read;
  for (int i = 0; i < n; i++) {
      scanf("%d%d", &x, &y);
      if (y > r) {
    flag = 1;
    continue;
      }

      t = sqrt(r * r - y * y);
      tmp[i].l = x - t;
      tmp[i].r = x + t;
  }

  printf("Case %d: ", cas++);
  if (flag)
      printf("-1\n");
  else {
      sort(tmp, tmp + n, cmp);
      int cnt = 1;
      double begin = tmp[0].r;
      for (int i = 1; i < n; i++) {
    if (tmp[i].l - begin <= 1e-4)   continue;
    cnt++;
    begin = tmp[i].r;
      }
      printf("%d\n", cnt);
  }
    }
    return 0;
}
