#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

ll solve (ll n, ll k) {
	ll sum = 0;

	if (n > k)
		sum += (n-k) * k;

	ll a = sqrt(k+0.5), b = k / a;
	for (ll i = a; i > 1; i--) {
		ll s = k / i;
		ll e = k / (i-1);

		if (s > n)
			break;

		if (e > n)
			e = n;

		sum += ( (k%(s+1) + k%e) * (e - s) / 2);
	}

	for (ll i = 2; i <= b && i <= n; i++)
		sum += k%i;
	return sum;
}

int main () {
	ll n, k;
	while (scanf("%lld%lld", &n, &k) == 2) {
		printf("%lld\n", solve(n, k));
	}
	return 0;
}
