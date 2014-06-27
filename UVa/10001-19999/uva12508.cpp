#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

inline ll max(ll a, ll b) {
	return a > b ? a : b;
}

inline ll min(ll a, ll b) {
	return a < b ? a : b;
}

ll N, M, A, B;

ll solve (ll k) {
	if (k < 0)
		k = 0;

	if (N > M)
		swap(N, M);

	ll ans = 0;
	for (ll n = 1; n <= N; n++) {
		for (ll m = 1; m <= M; m++) {
			ll cnt = 0;

			if (n * m <= k)
				cnt += 2 * (n + m - 2);

			ll l, r;
			for (ll x = 0; x <= n; x ++) {
				r = (m * x + k) / n;

				if (r > m)
					r = m;

				ll t = m * x - k;

				if(t <= 0) 
					l = 0;
				else 
					l = (t - 1) / n + 1;

				if(l <= r) 
					cnt += 2 * (r - l + 1);
			}

			for (ll x = 1; x < n; x++) {
				ll tmp = n * m - x;

				if (tmp <= k)
					cnt += 4 * (m - 1);
				else {
					tmp = tmp - k;
					ll u = m-1 - min(tmp / x + (tmp % x != 0), m-1);
					cnt += 4 * u;
				}
			}

			ans += cnt * (N - n + 1) * (M - m + 1);
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld%lld%lld%lld", &N, &M, &A, &B);
		printf("%lld\n", solve(B*2) - solve(A*2-1));
	}
	return 0;
}
