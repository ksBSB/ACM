#include <stdio.h>
#include <math.h>

int l, r;
double m, p, a, b, tmp, sum;

int main() {
    while (scanf("%lf%lf%lf%lf", &m, &p, &a, &b) == 4) {
  tmp = a * b;
  r = l = 0;
  sum = 0;
  for (int i = 0; i < m - 1; i++) {
      if (tmp < a) {
    tmp++;
    l++;
      }
      else {
    tmp -= a;
    r++;
      }
  }

  sum += l / pow(sqrt(a), p);
  sum += r * pow(sqrt(a), p);
  sum += pow((tmp / sqrt(a)), p);
  printf("%d\n", int(sum + 0.5));
    }
    return 0;
}
