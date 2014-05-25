#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 1205;
const double pi = 4 * atan(1.0);
const double eps = 1e-9;
typedef long long ll;

struct point {
	double x, y;
}p[N];
int n;
double r[N*2];

ll C (ll a, ll b) {
	if (a < b)
		return 0;

	ll ans = 1;
	for (ll i = 0; i < b; i++)
		ans = ans * (a-i) / (i+1);
	return ans;
}

ll count (int u) {
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (i == u)
			continue;

		double temp = atan2(p[u].y-p[i].y, p[u].x-p[i].x);
		r[c++] = temp;
		r[c++] = temp + pi*2;
	}
	sort(r, r + c);

	ll ans = 0, mv = 0;
	for (ll i = 0; i < n-1; i++) {
		double mitl = r[i] + pi / 2;
		while (fabs(r[mv]-r[i]) - pi/2 <= -eps)
			mv++;
		ans += (mv - i - 1);
	}
	return C(n-1, 2) - ans;
}

ll solve () {
	ll ans = 0;
	for (int i = 0; i < n; i++)
		ans += count(i);
	return C(n, 3) - ans;
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		printf("Scenario %d:\n", cas++);
		printf("There are %lld sites for making valid tracks\n", solve());
	}
	return 0;
}
