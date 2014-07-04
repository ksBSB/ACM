#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long ll;
const ll MOD = 100000007;

ll n;

int main () {
	while (scanf("%lld", &n) == 1 && n) {
		int cnt = 0;
		ll m = sqrt(n+0.5);
		for (ll i = 1; i <= m; i++) {
			if (n%i)
				continue;

			ll j = n / i;
			j -= 6 * i;

			if (j%7 || j <= 0)
				continue;

			ll r = (j/7) % MOD;

			ll ans = (2 * r * r) % MOD;
			if (ans == 0)
				continue;
			cnt++;
			printf("Possible Missing Soldiers = %lld\n", ans);
		}

		if (cnt == 0)
			printf("No Solution Possible\n");
		printf("\n");
	}
	return 0;
}
