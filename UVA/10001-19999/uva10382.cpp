#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int N = 10010;

struct Seg {
    double x;
    double y;
    friend bool operator < (const Seg&a,const Seg&b){  
  return a.x < b.x;  
    } 
}seg[N];
int n;
double order, h;

void input() {
    int sum = 0;
    double r, p;
    for (int i = 0; i < n; i++) {
  scanf("%lf%lf", &p, &r);
  if (h / 2 >= r) continue;
  double q = sqrt(r * r - h * h / 4.0);
  seg[sum].x = p - q;
  seg[sum].y = p + q;
  sum++;
    }
    n = sum;
}

int main() {
    while (scanf("%d%lf%lf", &n, &order, &h) == 3) {
  memset(seg, 0, sizeof(seg));
  input();

  sort(seg, seg + n);

  int cnt = 0;
  double begin = 0, over = 0;
  bool flag = false;
  if (seg[0].x <= 0) {
      int i = 0;

      while (i < n) {
    int j = i;
    while (j < n && begin >= seg[j].x) {
        if (seg[j].y > over)
      over = seg[j].y;
        j++;
    }
    if (i == j) break;

    cnt++;
    begin = over;
    i = j;
    if (begin >= order) {
        flag = true;
        break;
    }
      }
  }

  if (flag)
      printf("%d\n", cnt);
  else
      printf("-1\n");
    }
    return 0;
}
