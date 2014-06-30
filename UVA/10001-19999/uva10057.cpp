#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 1000005;
int n, num[N];
int count(int cur) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
  if (num[i] == num[cur])
      cnt++;
  else if (num[i] > num[cur])
      break;
    }
    return cnt;
}
int main() {
    int cur, cnt, sum;
    while (scanf("%d", &n) == 1) {
  cur = n / 2;
  for (int i = 0; i < n; i++)
      scanf("%d", &num[i]);
  sort(num, num + n);
  if (n % 2) {
      sum = count(cur);
      cnt = 1;
  }
  else {
      sum = count(--cur);
      if (num[cur] == num[cur + 1])
    cnt = 1;
      else {
    cnt = num[cur + 1] - num[cur] + 1;
    sum += count(cur + 1);
      }
  }
  printf("%d %d %d\n", num[cur], sum, cnt); 
    }
    return 0;
}
