#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;
const int N = 1005;
typedef long long ll;

int m;
ll c[N];

void init (ll k) {
	m = 0;

	ll t = sqrt(k);
	for (ll i = 1; i <= t; i++) {
		if (k % i == 0) {
			c[m++] = i;
			if (k / i != i)
				c[m++] = k / i;
		}
	}
	sort (c, c + m);
}

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a%b);
}

int solve (ll n) {
	int ans = 0;
	for (int i = 0; i < m; i++) {
		for (int j = i; j < m; j++) {
			if (c[i] * c[j] / gcd(c[i], c[j]) == n)
				ans++;
		}
	}
	return ans;
}

int main () {
	ll n;
	while (scanf("%lld", &n), n) {
		init (n);
		printf("%lld %d\n", n, solve(n));
	}
	return 0;
}