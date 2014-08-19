#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 5005;

int N, arr[maxn], dp[maxn][maxn];
ll x, val[maxn];

inline ll getval (int l, int r) {
	return val[r] - val[l-1];
}

void init () {
	memset(dp, -1, sizeof(dp));

	val[0] = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%I64d", &x);
		val[i] = val[i-1] + x;
	}
	
	for (int i = 1; i <= N; i++)
		scanf("%d", &arr[i]);
}

int solve (int l, int r) {

	if (l > r)
		return 0;

	if (dp[l][r] != -1)
		return dp[l][r];


	int& ret = dp[l][r];
	ret = arr[r-l+1];

	int mv = l;

	for (int i = r; i > l; i--) {
		ll u = getval(i, r);

		while (getval(l, mv) < u && mv < i)
			mv++;

		if (mv >= i)
			break;

		if (getval(l, mv) == u)
			ret = min(ret, arr[r-i+1] + arr[mv-l+1] + solve(mv+1, i-1));
	}
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();
		printf("%d\n", solve(1, N));
	}
	return 0;
}
