#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f;

ll X1, Y1, X2, Y2;
ll A, B, C;

ll gcd (ll a, ll b) {
	return b ? gcd(b, a%b) : a;
}

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

void init () {
	double a, b, c, d;
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	X1 = (ll)(a*10+0.5);
	Y1 = (ll)(b*10+0.5);
	X2 = (ll)(c*10+0.5);
	Y2 = (ll)(d*10+0.5);
	A = Y1-Y2;
	B = -(X1-X2);
	C = A * X1 + B * Y1;
	A *= 10;
	B *= 10;

	ll t = gcd (gcd(A, B), C);
	A /= t;
	B /= t;
	C /= t;

	if (X1 > X2)
		swap(X1, X2);
	if (Y1 > Y2)
		swap(Y1, Y2);
}

ll solve () {
	ll g, x, y;
	exgcd(A, B, g, x, y);

	//printf("%lld %lld %lld %lld %lld\n", A, B, C, x, y);
	if (C%g)
		return 0;

	ll up = INF, down = -INF;

	double dx = x * C * 1.0 / g;
	if (B / g > 0) {
		up = min(up, (ll)floor( (X2/10.0-dx) * g / B));
		down = max(down, (ll)ceil( (X1/10.0-dx) * g / B));
	} else if (B / g < 0) {
		up = min(up, (ll)floor( (X1/10.0-dx) * g / B));
		down = max(down, (ll)ceil( (X2/10.0-dx) * g / B));
	} else if (X1 % 10)
		return 0;

	double dy = y * C * 1.0 / g;
	if (A / g > 0) {
		up = min(up, (ll)floor( (dy-Y1/10.0) * g / A));
		down = max(down, (ll)ceil( (dy-Y2/10.0) * g / A));
	} else if (A / g < 0) {
		up = min(up, (ll)floor( (dy-Y2/10.0) * g / A));
		down = max(down, (ll)ceil( (dy-Y1/10.0) * g / A));
	} else if (Y1 % 10)
		return 0;

	if (up < down)
		return 0;
	return up - down + 1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
