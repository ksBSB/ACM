#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll solve (ll n, ll k) {
	ll ans = 0, sign = 1;
	while (n) {
		ans += sign * n;
		n /= k;
		sign *= -1;
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		ll n, k;
		scanf("%lld%lld", &n, &k);
		printf("%lld\n", solve(n, k));
	}
	return 0;
}
