#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
//typedef __int64 ll;
const ll mod = 1e9+9;
const int maxn = 1e5+10;
int n, m, l, r;
ll c[maxn];

ll pow_mod (ll x, int k) {
	ll ans = 1;
	while (k) {
		if (k&1)
			ans = ans * x % mod;

		x = x * x % mod;
		k /= 2;
	}
	return ans;
}

void init () {
	int x, p, q;
	l = r = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);

		if (l >= x)
			p = l - x;
		else if (r >= x)
			p = ( (l&1) == (x&1) ? 0 : 1);
		else
			p = x - r;

		if (r + x <= m)
			q = r + x;
		else if (l + x <= m)
			q = ( ((l+x)&1) == (m&1) ? m : m-1);
		else
			q = 2 * m - l - x;
		l = p;
		r = q;
	}
}

ll solve () {
	c[0] = 1;
	ll ans = 0;

	for (int i = 0; i <= r; i++) {

		if (i) {
			if (m - i < i)
				c[i] = c[m-i];
			else
				//c[i] = c[i-1] * (m-i+1) % mod * pow_mod(i, mod-2)  % mod;
				c[i] = c[i-1] * ( (ll)(m-i+1) * pow_mod(i, mod-2)  % mod) % mod;
		}

		if (i >= l && (i&1) == (l&1))
			ans = (ans + c[i]) % mod;
	}
	return ans;
}

int main () {
	while (scanf("%d%d", &n, &m) == 2) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
