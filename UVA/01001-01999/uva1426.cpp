#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;

ll X, N, R;
set<ll> ans;

void exgcd (ll a, ll b, ll& d, ll& x, ll& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		exgcd (b, a%b, d, y, x);
		y -= (a/b) * x;
	}
}

void solve (ll A, ll B, ll C) {
	ll d, x, y;
	exgcd(A, B, d, x, y);
	
	if (C % d)
		return;

	x = x * C / d;
	x = (x % (B/d) + (B/d))%(B/d);
	ll s = x * A - C / 2;
	ll k = A * B / d;
	for (ll i = s; i < N; i += k)
		if (i >= 0)
			ans.insert(i);

}

int main () {
	int cas = 1;
	while (scanf("%lld%lld%lld", &X, &N, &R) == 3 && X + N + R) {
		ans.clear();
		ll m = sqrt(N+0.5);
		for (ll i = 1; i <= m; i++) {
			if (N%i)
				continue;
			solve(i, N/i, 2*R);
			solve(N/i, i, 2*R);
		}

		printf("Case %d:", cas++);
		for (set<ll>::iterator i = ans.begin(); i != ans.end(); i++)
			printf(" %lld", *i);
		printf("\n");
	}
	return 0;
}
