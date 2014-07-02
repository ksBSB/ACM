#include <cstdio>
#include <cstring>

typedef long long ll;
const int maxn = 5;
const ll m[maxn] = {23,28,33};

ll M, t[maxn], D;

bool init () {
	bool flag = false;
	for (int i = 0; i < 3; i++) {
		scanf("%lld", &t[i]);
		if (t[i] != -1)
			flag = true;
	}

	scanf("%lld", &D);
	if (D != -1)
		flag = true;

	return flag;
}

void gcd (ll a, ll b, ll& d, ll& x, ll& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, d, y, x);
		y -= (a/b) * x;
	}
}

ll china (ll* a, int n) {
	M = 1;
	for (int i = 0; i < n; i++)
		M *= m[i];

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		ll w = M/m[i], d, x, y;
		gcd(m[i], w, d, x, y);

		ans = (ans + y*w*a[i]) % M;
	}
	ans = (ans + M) % M;
	return ans;
}

int main () {
	int cas = 1;
	while (init()) {
		ll ans = china(t,3);
		ll t = ans;
		while (ans < D || ans == 0)
			ans += M;
		printf("Case %d: the next triple peak occurs in %lld days.\n", cas++, ans - D);
	}
	return 0;
}
