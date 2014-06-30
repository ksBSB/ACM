#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;

const int N = 100010;
struct point {
    double x;
    double y;
}p[N];

bool cmp(const point &a, const point &b) {
    return a.x < b.x;
}

double getDist(point a, point b) {
    double tmpx = (a.x - b.x) * (a.x - b.x);
    double tmpy = (a.y - b.y) * (a.y - b.y);
    return sqrt(tmpx + tmpy);
}

int main() {
    int n;
    double Min, dist;
    while (scanf("%d", &n), n) {
  memset(p, 0, sizeof(p));
  Min = 0XFFFFFFF;
  for (int i = 0; i < n; i++)
      scanf("%lf %lf", &p[i].x, &p[i].y);
  sort(p, p + n, cmp);

  for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
    if (fabs(p[i].x - p[j].x) - Min > 1e-9)
        break;
    dist = getDist(p[i], p[j]);
    if (Min - dist > 1e-9)
        Min = dist;
      }
  }

  if (Min - 10000 > 1e-9)
      printf("INFINITY\n");
  else
      printf("%.4lf\n", Min);
    }
    return 0;
}
