#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

ll gcd (ll a, ll b) {
	return b ? gcd(b, a%b) : a;
}

int main () {
	ll L, u, v, t;
	while (scanf("%lld%lld%lld%lld", &L, &u, &v, &t) == 4 && L + u + v + t) {

		if (u == 0 && v == 0) {
			printf("0\n");
			continue;
		}

		ll ans = 0;
		if (u < v)
			swap(u, v);

		ans += (t * (u+v) + L) / (2*L);
		ans += (t * (u-v) + L) / (2*L);

		ll d = gcd(u, v);

		if ((u-v) / d % 2)
			ans -= (d * t + L) / (2*L);
		printf("%lld\n", ans);
	}
	return 0;
}
