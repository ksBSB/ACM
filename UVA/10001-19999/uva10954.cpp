#include <stdio.h>
#include <set>
using namespace std;

int n, ans;
multiset<int> s;

void solve() {
    int sum = 0;
    ans = 0;
    multiset<int>::iterator it1, it2;
    while (1) {
  if (s.size() == 1)  break;
  it1 = s.begin();
  it2 = it1++;
  sum = (*it1) + (*it2);
  s.erase(it1);
  s.erase(it2);
  ans += sum;
  s.insert(sum);
    }
    printf("%d\n", ans);
}

int main() {
    int a;
    while (scanf("%d", &n), n) {
  s.clear();
  for (int i = 0; i < n; i++) {
      scanf("%d", &a);
      s.insert(a);
  }
  solve();
    }
    return 0;
}
