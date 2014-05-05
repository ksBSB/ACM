#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll a, b, ans, v = 1;

ll solve (ll k) {
	ll x = b/k, c = b%k;
	ll ans = (a-k+2)*(a-k+2) +(k-2);
	ll tmp = c*(x+1)*(x+1) + (k-c)*x*x;
	return ans - tmp;
}

void put() {
	cout << ans << endl;

	ll x = b/v, c = b%v;
	bool flag = false;
	for (ll i = 1; i < v; i++) {
		if (flag) printf("o");
		for (ll j = 0; j < x; j++) printf("x");
		if (i <= c) printf("x");
		flag = true;
	}
	for (ll i = 0; i < (a-v+2); i++) printf("o");
	for (ll i = 0; i < x; i++) printf("x");
	printf("\n");
}

int main () {
	ans = -INF;
	cin >> a >> b;

	if (a == 0) {
		cout << b*b*(-1) << endl;
		for (ll i = 0; i < b; i++) printf("x");
		printf("\n");
		return 0;
	}

	for (ll i = 2; i <= a + 1; i++) {
		ll t = solve(i);
		if (t > ans) {
			ans = t; v = i;
		}
	}

	put();
	return 0;
}
