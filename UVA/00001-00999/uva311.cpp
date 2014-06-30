#include <stdio.h>
const int N = 7;
int sum[N], n;
const int one[] = {0, 7, 6, 5};
const int two[] = {0, 5, 3, 1};

int main() {
    while (1) {
  // Read;
  int flag = 1;
  n = 0;
  for (int i = 1; i < N; i++) {
      scanf("%d", &sum[i]);
      if (sum[i])
    flag = 0;
  }
  if (flag)   break;

  int total = sum[6] + sum[5] + sum[4] + (sum[3] + 3) / 4;
  int numOne = sum[5] * 11 + one[sum[3] % 4];
  int numTwo = sum[4] * 5 + two[sum[3] % 4];
  if (numTwo < sum[2]) {
      int cur = sum[2] - numTwo;
      int tmp = (cur + 8) / 9;
      total += tmp;
      numOne += 4 * (9 * tmp - cur); 
  }
  else
      numOne += 4 * (numTwo - sum[2]);

  if (numOne < sum[1])
      total += (sum[1] - numOne + 35) / 36;
  printf("%d\n", total);
    }
    return 0;
}
