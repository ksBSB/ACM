#include <stdio.h>
int max(const int &a, const int &b) { return a > b ? a : b;}
int min(const int &a, const int &b) { return a > b ? b : a;}

int main() {
    int cas, n, len, Max, Min, dist;
    scanf("%d", &cas);
    while (cas--) {
  Max = Min = 0;
  scanf("%d%d", &len, &n);
  for (int i = 0; i < n; i++) {
      scanf("%d", &dist);
      Max = max(Max, max(dist, len - dist));
      Min = max(Min, min(dist, len - dist));
  }
  printf("%d %d\n", Min, Max);
    }
    return 0;
}
