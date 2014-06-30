#include <cstdio>
#include <cstring>

typedef long long ll;

ll solve (ll left) {

	if (left < 0)
		return 0;

	ll ans = 1, right = 0, x = 1;

	while (left >= 10) {
		ll mid = left % 10;
		left /= 10;

		if (mid)
			ans += left * x;
		else
			ans += (left - 1) * x +  (right + 1);

		right = right + mid * x;
		x *= 10;
	}
	return ans;
}

int main () {
	ll n, m;
	while (scanf("%lld%lld", &n, &m) == 2 && n != -1 && m != -1) {
		printf("%lld\n", solve(m) - solve(n-1));
	}
	return 0;
}
