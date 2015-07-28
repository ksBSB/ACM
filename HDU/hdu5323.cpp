#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f;

ll L, R, N;

void dfs(ll l, ll r) {
	//printf("%lld %lld\n", l, r);
	if (l <= 0 || r >= 2 * R) {
		if (l == 0)
			N = min(N, r);
		return;
	}

	int k = r - l + 1;

	if (k > l)
		return;


	dfs(l - k, r);
	dfs(l - k - 1, r);

	dfs(l, r + k);
	if (k > 1)
		dfs(l, r + k - 1);
}

int main () {
	while (scanf("%lld%lld", &L, &R) == 2) {
		N = inf;
		dfs(L, R);
		printf("%lld\n", N == inf ? -1 : N);
	}
	return 0;
}
