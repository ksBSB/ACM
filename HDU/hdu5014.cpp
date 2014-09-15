#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;
typedef long long ll;

int arr[maxn];

ll solve (int n) {
	if (n < 0)
		return 0;

	int k = 0;
	while ((1<<k) <= n) k++;
	int t = (1<<k) - 1;
	ll ret = 0;

	for (int i = t - n; i <= n; i++) {
		ret += t;
		arr[i] = t - i;
	}

	ret += solve(t - n - 1);
	return ret;
}

int main () {
	int n, x;
	while (scanf("%d", &n) == 1) {
		printf("%lld\n", solve(n));
		for (int i = 0; i <= n; i++) {
			scanf("%d", &x);
			printf("%d%c", arr[x], i == n ? '\n' : ' ');
		}
	}
	return 0;
}
