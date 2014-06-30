#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 10005;
bool cmp (int a, int b) { return a > b; }
int n, d[N];

bool judge() {
    for (int i = 0; i < n - 1; i++) {
  sort(d + i, d + n, cmp);
  if (i + d[i] >= n)  return false;
  for (int j = i + 1; j <= i + d[i]; j++) {
      d[j]--;
      if (d[j] < 0)   return false;
  }
    }
    return d[n - 1] != 0 ? false : true;
}

int main() {
    int flag, sum;
    while (scanf("%d", &n), n) {
  flag = 1;
  sum = 0;
  memset(d, 0, sizeof(d));
  for (int i = 0; i < n; i++) {
      scanf("%d", &d[i]);
      if (d[i] >= n)  flag = 0;
      sum += d[i];
  }
  if (sum % 2)  flag = 0;
  printf("%s\n", (flag && judge()) || sum == 0 ? "Possible" : "Not possible");
    }
    return 0;
}
