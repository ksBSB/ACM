#include <stdio.h>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1005;
int num[N];
vector<int> sum;

int main() {
    int n, m, v, cas = 1;
    vector<int>::iterator it;
    while (scanf("%d", &n) == 1 && n) {
  sum.clear();
  for (int i = 0; i < n; i++) {
      scanf("%d", &num[i]);
      for (int j = 0; j < i; j++)
    sum.push_back(num[i] + num[j]);
  }
  sort(sum.begin(), sum.end());

  scanf("%d", &m);
  printf("Case %d:\n", cas++);
  for (int i = 0; i < m; i++) {
      scanf("%d", &v);
      it = lower_bound(sum.begin(),sum.end(), v);
      int Min = *it;
      if (it != sum.begin() && abs(*(it - 1) - v) < abs(Min - v))
    Min = *(it - 1);
      printf("Closest sum to %d is %d.\n", v, Min);  
  }
    }
    return 0;
}
