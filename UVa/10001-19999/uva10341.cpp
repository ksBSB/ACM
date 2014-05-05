#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

double p, q, r, s, t, u, cur;
double count(double x) {
    return p * exp(-x)  + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main() {
    while (scanf("%lf%lf%lf%lf%lf%lf", &p, &q, &r, &s, &t, &u) == 6) {
  double a = 0, b = 1;
  if (count(a) * count(b) > 0)
      printf("No solution\n");
  else if (fabs(count(0)) <= 0.0001)
      printf("0.0000\n");
  else if (fabs(count(1)) <= 0.0001)
      printf("1.0000\n");
  else {
      if (count(0) > 0) {
    a = 1;
    b = 0;
      }
      else {
    a = 0;
    b = 1;
      }
      while (1) {
    cur = (a + b) / 2;
    if (fabs(count(cur)) <= 0.00000001)
        break;
    else if(count(cur) > 0)
        b = cur;
    else
        a = cur;
      }
      printf("%.4lf\n", cur);
  }
    }
    return 0;
}
