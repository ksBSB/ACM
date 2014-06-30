#include <stdio.h>
#include <string.h>
const int M = 32;

long long T, L, R;
int tmp[M + 1], Max[M + 1], Min[M + 1], ans[M + 1];

void getBase(long long cur, int now[]) {
    memset(now, 0, sizeof(now));
    for (int i = 0; i <= M; i++) {
  now[i] = cur % 2;
  cur /= 2;
    }
}

long long solve() {
    getBase(T, tmp);
    getBase(R, Max);
    getBase(L, Min);
    int Maxflag = 0, Minflag = 0;
    memset(ans, 0, sizeof(ans));

    for (int i = M; i >= 0; i--) {
  if (tmp[i] == 0 && Maxflag) {
      ans[i] = 1;
      if (Min[i] == 0)    Minflag = 1;
  }
  else if (tmp[i] && Minflag) {
      ans[i] = 0;
      if (Max[i]) Maxflag = 1;
  }
  else if (tmp[i]) {
      if (Min[i] == 0) {
    ans[i] = 0;
    if (Max[i]) Maxflag = 1;
      }
      else if (Min[i])  ans[i] = 1;
  }
  else {
      if (Max[i]) {
    ans[i] = 1;
    if (Min[i] == 0)    Minflag = 1;
      }
      else if (Max[i] == 0)   ans[i] = 0;
  }
    }

    long long sum = 0;
    for (int i = M; i >= 0; i--)
  sum = sum * 2 + ans[i];

    return sum;
}

int main() {
    while (scanf("%lld%lld%lld", &T, &L, &R) == 3) {
  printf("%lld\n", solve());
    }
    return 0;
}
