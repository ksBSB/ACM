#include <stdio.h>
#include <string.h>
const int N = 20005;

int maxsum(int *A, int x, int y, int &frist, int &end) {
    if (x == y - 1) {
  frist = x;
  end = y;
  return A[x];
    }

    int cur = x + (y - x) / 2;
    int p1, p2, p3, q1, q2, q3, Max, v, L = A[cur - 1], R = A[cur];
    int a = maxsum(A, x, cur, p1, q1);
    int b = maxsum(A, cur, y, p2, q2);

    if (a > b) {
  Max = a;
  frist = p1, end = q1;
    } 
    else if (a < b) {
  Max = b;
  frist = p2, end = q2;
    }
    else {
  Max = b;
  if (q1 - p1 >= q2 - p2)
      frist = p1, end = q1;
  else
      frist = p2, end = q2;
    }

    v = 0, p3 = cur - 1;
    for (int i = cur - 1; i >= x; i--) {
  v += A[i];
  if (v >= L) {
      L = v;
      p3 = i;
  }
    }

    v = 0, q3 = cur;
    for (int i = cur; i < y; i++) {
  v += A[i];
  if (v >= R) {
      R = v;
      q3 = i;
  }
    }
    q3++;

    if (Max < R + L) {
  frist = p3, end = q3;
  return R + L;
    }
    else if (Max > R + L)
  return Max;
    else {
  if (q3 - p3 > end - frist)
      frist = p3, end = q3;
  else if (q3 - p3 == end - frist && p3 < frist)
      frist = p3, end = q3;
  return Max;
    }
}

int sta[N];
int main() {
    int t, cas = 1, n, frist, end;
    scanf("%d", &t);
    while (t--) {
  scanf("%d", &n);
  memset(sta, 0, sizeof(sta));
  for (int i = 0; i < n - 1; i++)
      scanf("%d", &sta[i]);
  if (maxsum(sta, 0, n - 1, frist, end) < 0)
      printf("Route %d has no nice parts\n", cas++);
  else
      printf("The nicest part of route %d is between stops %d and %d\n", cas++, frist + 1, end + 1);
    }
    return 0;
}
