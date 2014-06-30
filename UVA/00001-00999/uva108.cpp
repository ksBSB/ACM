#include <stdio.h>
#include <string.h>
const int N = 105;
const int Min = -2147483645;

int maxsum(int A[], int x, int y) {
    if (y - x == 1) return A[x];
    int cur = x + (y - x) / 2;
    int a = maxsum(A, x, cur), b = maxsum(A, cur, y);
    int Max = a > b ? a : b;
    int v = 0, L = A[cur - 1], R = A[cur];
    for (int i = cur - 1; i >= x; i--) {
  v += A[i];
  L = v > L ? v : L;
    }
    v = 0;
    for (int i = cur; i < y; i++) {
  v += A[i];
  R = v > R ? v : R;
    }
    return Max > R + L ? Max : R + L;
}

int num[N][N], sum[N];
int main() {
    int n, Max, total;
    while (scanf("%d", &n) == 1) {
  // Init;
  Max = Min;
  memset(num, 0, sizeof(num));
    
  // Read;
  for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
    scanf("%d", &num[i][j]);
  // Count;
  for (int i = 0; i < n; i++) {
      memset(sum, 0, sizeof(sum));
      for (int j = i; j < n; j++) {
    for (int k = 0; k < n; k++)
        sum[k] += num[j][k];
    total = maxsum(sum, 0, n);
    if (total > Max)
        Max = total;
      }
  }
  // Printf;
  printf("%d\n", Max);
    }
    return 0;
}
