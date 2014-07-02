#include <cstdio>
#include <cstring>

typedef long long ll;

const int maxn = 1e6;
ll lower, up, prime[maxn];
int cp, v[maxn];

void primeTable (int n) {

	cp = 0;
	memset(v, 0, sizeof(v));

	for (int i = 2; i <= n; i++) {
		if (v[i])
			continue;

		prime[cp++] = i;
		for (int j = 2 * i; j <= n; j += i)
			v[j] = 1;
	}
}

ll solve (ll n) {
	ll ans = 0;

	for (int i = 0; i < cp; i++) {
		ll u = prime[i] * prime[i];

		if (u > n)
			break;

		while (u <= n) {
			u *= prime[i];
			ans++;
		}
	}
	return ans;
}

int main () {
	primeTable(maxn);
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld%lld", &lower, &up);
		printf("%lld\n", solve(up) - solve(lower-1));
	}
	return 0;
}
