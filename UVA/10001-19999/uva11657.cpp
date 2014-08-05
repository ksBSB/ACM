#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll m, n, x0, y0, x1, y1, p, q;

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

bool judge () {
	if (p == 0 || q == 0) {
		ll u = p * (y1-y0) - q * (x1-x0);
		return u == 0;
	}

	ll absq = q < 0 ? -q : q;
	ll absp = p < 0 ? -p : p;
	m *= absq; x0 *= absq; x1 *= absq;
	n *= absp; y0 *= absp; y1 *= absp;
	p /= absp; q /= absq;

	ll d1 = q * (y1-y0) - p * (x1-x0);
	ll d2 = q * (y1-y0) - p * (2*m-x1-x0);
	ll d3 = q * (2*n-y1-y0) - p * (x1-x0);
	ll d4 = q * (2*n-y1-y0) - p * (2*m-x1-x0);
	ll g = gcd(2*m, 2*n);
	
	if (d1 % g == 0) return true;
	if (d2 % g == 0) return true;
	if (d3 % g == 0) return true;
	if (d4 % g == 0) return true;
	return false;
}

int main () {
	while (scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &m, &n, &x0, &y0, &x1, &y1, &p, &q) == 8) {
		if (!(m || n || x0 || y0 || x1 || y1 || p || q))
			break;
		printf("%s\n", judge() ? "HIT" : "MISS");
	}
	return 0;
}
