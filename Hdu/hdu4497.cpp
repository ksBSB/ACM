#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

typedef long long ll;
ll g, l;

ll solve () {
	if (l%g)
		return 0;

	ll ans = 1;
	ll k = l / g;
	ll t = sqrt((double)k);

	for (ll i = 2; i <= t; i++) {
		if (k % i)
			continue;

		ll c = 0;
		while (k%i == 0) {
			c++;
			k /= i;
		}

		ans = ans * 6 * c;
	}

	if (k != 1)
		ans = ans * 6;

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		cin >> g >> l;
		cout << solve() << endl;
	}
	return 0;
}
