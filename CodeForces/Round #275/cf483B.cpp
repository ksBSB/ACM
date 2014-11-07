#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}

ll c1, c2, x, y, v;
bool judge(ll m, ll v) {
	ll a = m - m / x;
	ll b = m - m / y;

	if (a < c1 || b < c2)
		return false;

	ll t = m - m / x - m / y + m / v;
	if (a + b - t < c1 + c2)
		return false;
	return true;
}

int main () {

	scanf("%lld%lld%lld%lld", &c1, &c2, &x, &y);
	ll l = 1, r = 1e9 * 2, m;
	v = lcm(x, y);
	for (int i = 0; i < 100; i++) {
		m = (l + r) >> 1;
		if (judge(m, v))
			r = m;
		else
			l = m;
	}
	printf("%lld\n", r);
	return 0;
}
