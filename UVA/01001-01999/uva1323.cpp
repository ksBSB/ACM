/**********************
 * 梅森素数，(2^k) - 1
 *
 * 一个数若能差分成若干个不同的梅森素数的积，那么该数的所有因子和可以写成2^n形式。
 *
**********************/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxp = 8;
const int f[maxp+5] = {2, 3, 5, 7, 13, 17, 19, 31};
int N, ans, s[105];
ll  mpri[maxp+5];

void insert (ll u) {
	s[N] = 0;
	for (int i = 0; i < maxp; i++) {
		if (u % mpri[i] == 0) {
			s[N] |= (1<<i);
			u /= mpri[i];

			if (u % mpri[i] == 0)
				return;
		}
	}
	if (u == 1)
		N++;
}

int solve (int S) {
	int ret = 0;
	for (int i = 0; i < maxp; i++)
		if (S&(1<<i))
			ret += f[i];
	return ret;
}

void dfs (int d, int S) {

	ans = max(ans, solve(S));
	for (int i = d; i < N; i++)
		if ((S&s[i]) == 0)
			dfs(i+1, S|s[i]);
}

int main () {
	for (int i = 0; i < maxp; i++)
		mpri[i] = (1LL<<f[i]) - 1;

	ll n, a;
	while (scanf("%lld", &n) == 1) {
		N = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &a);
			insert(a);
		}

		if (N == 0)
			printf("NO\n");
		else {
			ans = 0;
			dfs(0, 0);
			printf("%d\n", ans);
		}
	}
	return 0;
}
