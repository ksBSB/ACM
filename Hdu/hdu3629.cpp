#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 1205;
const double pi = 4 * atan(1.0);
const double eps = 1e-9;

int n;
ll s;
double r[2*N];
struct point {
	double x, y;
}p[N];

ll Count (int d) {
	int c = 0, mv = 0;
	for (int i = 0; i < n; i++) {
		if (i == d)
			continue;

		double a = atan2(p[i].y-p[d].y, p[i].x-p[d].x);
		r[c] = a;
		r[c+n-1] = a + 2*pi;
		c++;
	}

	c = 2 * n - 2;
	sort(r, r + c);

	ll ans = 0;

	for (int i = 0; i < n-1; i++) {
		double tmp = r[i] + pi;

		while (tmp > r[mv])
			mv++;
		ll cnt = mv - i - 1;
		ans = ans + cnt * (cnt-1) / 2;
	}
	return s - ans;
}

ll solve () {
	s = (n-1) * (n-2) * (n-3) / 6;
	ll c = s * n / 4;
	ll ans = 0;

	for (int i = 0; i < n; i++)
		ans += Count(i);

	return c - ans;
}

int main () {
	int cas;
	cin >> cas;
	while (cas--) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> p[i].x >> p[i].y;
		cout << solve() << endl;
	}
	return 0;
}
