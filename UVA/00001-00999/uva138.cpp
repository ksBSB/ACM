#include <stdio.h>
#include <string.h>

long long count(long long a, long long b) {
  long long sum = (a + b) * (b - a + 1) / 2;
  return sum;
}

bool search(int b) {
  long long p, q;
  int l = 0, r = b;
  while (l < r) {
    int mid = (l + r) / 2;
    p = count(1, mid - 1), q = count(mid + 1, b);
    if (p < q)  l = mid;
    else if (p > q) r = mid;
    else {
      printf("%10d%10d\n", mid, b);
      return true;
    }
    if (l == r - 1) break;
  }
  return false;
}

int main () {
  int cnt = 0;
  for (int i = 4; cnt < 10; i++)
    if (search(i)) cnt++;
  return 0;
}
