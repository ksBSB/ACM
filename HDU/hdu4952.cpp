#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int main () {
	int cas = 1;
	ll n, k;

	while (scanf("%I64d%I64d", &n, &k) == 2 && n + k) {
		ll x = n, a = n;

		for (ll i = 2; i <= k; i++) {
			ll tmp = (x - 1) / i + 1;

			if (tmp == a)
				break;

			a = tmp;
			x = a * i;
		}

		printf("Case #%d: %I64d\n", cas++, a * k);
	}
	return 0;
}
