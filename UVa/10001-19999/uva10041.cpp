#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

const int N = 30005;
int peo[N];

int main() {
    int cas, n, sum;
    scanf("%d", &cas);
    while (cas--) {
  sum = 0;
  memset(peo, 0, sizeof(peo));
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
      scanf("%d", &peo[i]);

  sort(peo, peo + n);

  int cur = peo[(n + 1) / 2 - 1];
  for (int i = 0; i < n; i++)
      sum += abs(cur - peo[i]);
  printf("%d\n", sum);
    }
    return 0;
}
