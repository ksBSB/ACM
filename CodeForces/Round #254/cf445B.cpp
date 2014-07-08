#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 50;
typedef long long ll;

int n, m, f[maxn+5];

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

ll power (ll x, int t) {
	ll ans = 1;
	while (t) {
		if (t&1)
			ans = ans * x;

		x = x * x;
		t /= 2;
	}
	return ans;
}

int main () {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++)
		f[i] = i;

	int c = n, a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		int fa = getfar(a);
		int fb = getfar(b);

		if (fa != fb) {
			f[fa] = fb;
			c--;
		}
	}

	printf("%lld\n", power(2LL, n-c));
	return 0;
}
