#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 200000;

int np, pri[maxn+5], vis[maxn+5];

void priTable (int n) {
	np = 0;
	memset(vis, 0, sizeof(vis));

	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;
		pri[np++] = i;
		for (int j = 2*i; j <= n; j += i)
			vis[j] = 1;
	}
}

ll N;

inline ll count (ll n) {
	return n * n * n - 1;
}

inline ll fcount (ll n) {
	int ans = 0;
	for (int i = 0; i < np && pri[i] <= n; i++) {
		if (n < maxn && !vis[n]) {
			ans++;
			break;
		}

		if (n%pri[i] == 0) {
			ans++;
			n /= pri[i];
			if (n%pri[i] == 0)
				return 0;
		}
	}
	return ans&1 ? -1 : 1;
}

ll solve () {
	ll ans = count(N+1);
	for (ll i = 2; i <= N; i++) {
		ll t = fcount(i);
		ans += count(N/(2*i) * 2 + 1) * t;
	}
	return ans;
}

int main () {
	int cas = 1;
	priTable(maxn);
	while (scanf("%lld", &N) == 1 && N) {
		printf("Crystal %d: %lld\n", cas++, solve());
	}
	return 0;
}
