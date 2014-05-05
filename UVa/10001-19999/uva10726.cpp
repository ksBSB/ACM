#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long ll;
ll s, m, l, r;

int solve () {
	if (log2(s-1) * s > 32)
		return 0;

	ll t = s * (s - 1);
	ll d = m * (s - 1);
	ll p = pow(s, s);
	ll q = pow(s-1, s);

	int ans = 0;

	for (ll i = t; i <= 1e8; i += t) {
		ll u = (i + d) * p;

		if (u % q)
			continue;

	   	u = u / q - d;

		if (u > r) 
			break;

		if (u >= l)
			ans++;
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%lld%lld%lld%lld", &s, &m, &l, &r);
		printf("Case %d: %d\n", i, solve());
	}
	return 0;
}
