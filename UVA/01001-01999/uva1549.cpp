#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1.0);
typedef long long ll;

ll solve (ll R) {
	ll ret = 0;

	ll r = R, M = R * R;
	for (ll i = 0; i <= R; i++) {
		while (r * r + i * i > M)
			r--;
		ret += r;
	}
	return 4 * ret + 1;
}

int main () {
	ll n;
	while (scanf("%lld", &n) == 1) {
		printf("%lld\n%lld\n", n, solve(n));
	}
	return 0;
}
