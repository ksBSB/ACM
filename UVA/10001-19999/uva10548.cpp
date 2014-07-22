#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f;

ll A, B, C;

void gcd (ll a, ll b, ll& d, ll& x, ll& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, d, y, x);
		y -= (a/b) * x;
	}
}

void solve () {
	ll d, x, y;
	gcd(A, B, d, x, y);

	if (C % d) {
		printf("Impossible\n");
		return;
	}

	ll up = INF, lower = -INF;

	if (B / d > 0)
		lower = max(lower, (ll)ceil( (-1.0*x*C) / B) );
	else
		up = min(up, (ll)floor( (-1.0*x*C) / B) );

	if (A / d > 0)
		up = min(up, (ll)floor( (1.0*y*C) / A));
	else
		lower = max(lower, (ll)ceil( (1.0*y*C) / A));

	if (up == INF || lower == -INF)
		printf("Infinitely many solutions\n");
	else if (up < lower)
		printf("Impossible\n");
	else
		printf("%lld\n", up - lower + 1);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld%lld%lld", &A, &B, &C);
		solve();
	}
	return 0;
}
