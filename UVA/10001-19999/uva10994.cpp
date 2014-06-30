#include <stdio.h>
#define ll long long
ll ans;

ll f(ll x) {
	if (x == 0)	return 0;
	else if (x % 10)
		return x % 10;
	else 
		return  f(x / 10);
}

void solve(ll l, ll r) {
	if (r - l < 9) {
		for (int i = l; i <= r; i++)
			ans += f(i);
		return;
	}
	
	while (l % 10) {
		ans += f(l);
		l++;
	}

	while (r % 10) {
		ans += f(r);
		r--;
	}
	ans += 45 * (r - l) / 10;
	solve(l / 10, r / 10);
}

int main () {
	ll l, r;
	while (scanf("%lld%lld", &l, &r), l >= 0 || r >= 0) {
		ans = 0;
		solve(l, r);
		printf("%lld\n", ans);
	}
	return 0;
}
