#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll M, P;
ll gcd (ll a, ll b) { return b == 0 ? a : gcd(b, a%b); }

ll lower(ll x) {
	ll k = x / P;
	while (k * P + M >= x) k--;
	return k;
}

ll upper(ll x) {
	ll k = x / P;
	while (k * P + M <= x) k++;
	return k;
}

ll solve (ll a, ll b, ll c, ll d, ll m, ll p) {
	M = m, P = p;
	ll ret = 0, l, r, v, u;

	l = upper(a + c - 1);
	r = lower(d + a);
	u = l*P+M - (a+c) + 1;
	v = r*P+M - (a+c) + 1;
	if (r >= l) ret += (u + v) * (r - l + 1) / 2;

	l = upper(d + a - 1);
	r = lower(b + c + 1);
	if (r >= l) ret += (r - l + 1) * (d-c+1);
//	printf("%lld %lld %lld %lld\n", r-l+1, b-a+1, ret - 6, (r - l + 1) * (b-a+1));

	l = upper(b + c);
	r = lower(b + d + 1);
	u = (b+d) - (l*P+M) + 1;
	v = (b+d) - (r*P+M) + 1;
	if (r >= l) ret += (u + v) * (r - l + 1) / 2;
//	printf("%lld\n", ret);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		ll a, b, c, d, m, p;
		scanf("%lld%lld%lld%lld%lld%lld", &a, &b, &c, &d, &p, &m);
		if (b - a < d - c) {
			swap(a, c);
			swap(b, d);
		}

		ll up = solve(a, b, c, d, m, p), dn = 1LL * (b - a + 1) * (d - c + 1);
		ll g = gcd(up, dn);
		printf("Case #%d: %lld/%lld\n", kcas, up / g, dn / g);
	}
	return 0;
}
